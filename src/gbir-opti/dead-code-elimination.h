#pragma once
#include <gbir/basic-block.h>
#include <gbir/value.h>
#include <memory>
#include <unordered_map>
#include <vector>

namespace gbir
{
    class DeadCodeElimination
    {
    public:
        void run(std::vector<std::unique_ptr<GbirBasicBlock>>& blocks);

    private:
        std::vector<GbirValue> operands_of(GbirInst* inst);
        bool result_of(GbirInst* inst, int& out_id);
        bool has_side_effect(GbirInst* inst);

        std::unordered_map<int, int> use_count_;
        std::unordered_map<int, GbirInst*> def_inst_;
    };
} // namespace gbir
