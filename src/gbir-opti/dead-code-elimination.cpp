#include <gbir-opti/dead-code-elimination.h>

#include <gbir/inst/binop.h>
#include <gbir/inst/call.h>
#include <gbir/inst/const.h>
#include <gbir/inst/enters.h>
#include <gbir/inst/global.h>
#include <gbir/inst/mem.h>
#include <gbir/inst/phi.h>
#include <gbir/inst/scene.h>
#include <gbir/inst/terminator.h>

#include <unordered_set>

namespace gbir
{
    // Mark-and-sweep dead code elimination
    void
    DeadCodeElimination::run(std::vector<std::unique_ptr<GbirBasicBlock>>& blocks)
    {
        use_count_.clear();
        def_inst_.clear();

        for (auto& block : blocks)
        {
            for (auto& inst : block->instructions_get())
            {
                int result_id;
                if (result_of(inst.get(), result_id))
                    def_inst_[result_id] = inst.get();
                for (auto operand : operands_of(inst.get()))
                    use_count_[operand.id_get()]++;
            }
            if (block->has_terminator())
                for (auto operand : operands_of(&block->terminator_get()))
                    use_count_[operand.id_get()]++;
        }

        std::vector<GbirInst*> worklist;
        for (auto& [id, inst] : def_inst_)
            if (use_count_[id] == 0 && !has_side_effect(inst))
                worklist.push_back(inst);

        std::unordered_set<GbirInst*> dead;
        while (!worklist.empty())
        {
            GbirInst* inst = worklist.back();
            worklist.pop_back();
            if (!dead.insert(inst).second)
                continue;

            for (auto operand : operands_of(inst))
            {
                int id = operand.id_get();
                if (--use_count_[id] != 0)
                    continue;
                auto it = def_inst_.find(id);
                if (it != def_inst_.end() && !has_side_effect(it->second))
                    worklist.push_back(it->second);
            }
        }

        for (auto& block : blocks)
            std::erase_if(block->instructions_get(),
                          [&](const std::unique_ptr<GbirInst>& up)
                          { return dead.contains(up.get()); });
    }

    std::vector<GbirValue> DeadCodeElimination::operands_of(GbirInst* inst)
    {
        std::vector<GbirValue> operands;
        if (auto* load = dynamic_cast<LoadInst*>(inst))
            operands.push_back(load->read_value_get());
        else if (auto* binop = dynamic_cast<BinopInst*>(inst))
        {
            operands.push_back(binop->left_get());
            operands.push_back(binop->right_get());
        }
        else if (auto* call = dynamic_cast<CallInst*>(inst))
            for (auto arg : call->args_get())
                operands.push_back(arg);
        else if (auto* store = dynamic_cast<StoreInst*>(inst))
        {
            operands.push_back(store->target_get());
            operands.push_back(store->value_get());
        }
        else if (auto* ret = dynamic_cast<ReturnInst*>(inst))
            operands.push_back(ret->value_get());
        else if (auto* cond = dynamic_cast<CondBranchInst*>(inst))
            operands.push_back(cond->condition_get());
        else if (auto* phi = dynamic_cast<PhiInst*>(inst))
            for (auto& incoming : phi->incoming_get())
                operands.push_back(incoming.first);
        return operands;
    }

    bool DeadCodeElimination::result_of(GbirInst* inst, int& out_id)
    {
        if (auto* mem = dynamic_cast<MemInst*>(inst))
            out_id = mem->result_get().id_get();
        else if (auto* binop = dynamic_cast<BinopInst*>(inst))
            out_id = binop->result_get().id_get();
        else if (auto* call = dynamic_cast<CallInst*>(inst))
            out_id = call->result_get().id_get();
        else if (auto* konst = dynamic_cast<ConstInst*>(inst))
            out_id = konst->result_get().id_get();
        else if (auto* global = dynamic_cast<GlobalAddrInst*>(inst))
            out_id = global->result_get().id_get();
        else if (auto* phi = dynamic_cast<PhiInst*>(inst))
            out_id = phi->result_get().id_get();
        else
            return false;
        return true;
    }

    bool DeadCodeElimination::has_side_effect(GbirInst* inst)
    {
        return dynamic_cast<StoreInst*>(inst) || dynamic_cast<CallInst*>(inst)
            || dynamic_cast<EnterInst*>(inst) || dynamic_cast<StartInst*>(inst);
    }
} // namespace gbir
