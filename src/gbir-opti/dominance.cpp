#include <gbir-opti/dominance.h>

#include <algorithm>

#include "gbir/basic-block.h"

namespace gbir
{
    void
    Dominance::compute(std::vector<std::unique_ptr<GbirBasicBlock>>& blocks)
    {
        if (blocks.empty())
            return;

        postorder_.clear();
        po_num_.clear();
        visited_.clear();
        idom_.clear();
        frontier_.clear();
        next_po_num = 0;

        GbirBasicBlock* entry = blocks.front().get();
        dfs_postorder(entry);
        compute_idoms(entry);
        compute_frontiers();
    }

    void Dominance::dfs_postorder(GbirBasicBlock* block)
    {
        if (visited_.contains(block))
            return;
        visited_.insert(block);
        for (auto succ : block->successors_get())
            dfs_postorder(succ);
        postorder_.push_back(block);
        po_num_.insert({ block, next_po_num++ });
    }

    // Cooper Harvey Kennedy
    void Dominance::compute_idoms(GbirBasicBlock* entry)
    {
        for (auto bb : postorder_)
            idom_[bb] = nullptr;
        idom_[entry] = entry;
        bool changed = true;
        while (changed)
        {
            changed = false;
            for (auto it = postorder_.rbegin(); it != postorder_.rend(); ++it)
            {
                if (*it == entry)
                    continue;
                GbirBasicBlock* new_idom = nullptr;
                for (auto pred : (*it)->predecessors_get())
                {
                    if (idom_[pred] != nullptr)
                    {
                        if (new_idom == nullptr)
                            new_idom = pred;
                        else
                            new_idom = intersect(pred, new_idom);
                    }
                }
                if (idom_[*it] != new_idom)
                {
                    idom_[*it] = new_idom;
                    changed = true;
                }
            }
        }
    }

    GbirBasicBlock* Dominance::intersect(GbirBasicBlock* a, GbirBasicBlock* b)
    {
        while (a != b)
        {
            while (po_num_[a] < po_num_[b])
                a = idom_[a];
            while (po_num_[b] < po_num_[a])
                b = idom_[b];
        }
        return a;
    }

    void Dominance::compute_frontiers()
    {
        for (auto bb : postorder_)
            frontier_[bb];

        for (auto bb : postorder_)
        {
            auto preds = bb->predecessors_get();
            if (preds.size() < 2)
                continue;

            for (auto pred : preds)
            {
                GbirBasicBlock* runner = pred;
                while (runner != idom_[bb])
                {
                    auto& df = frontier_[runner];
                    if (std::find(df.begin(), df.end(), bb) == df.end())
                        df.push_back(bb);
                    runner = idom_[runner];
                }
            }
        }
    }

    GbirBasicBlock* Dominance::idom_get(GbirBasicBlock* block)
    {
        auto it = idom_.find(block);
        if (it == idom_.end())
            return nullptr;
        return it->second;
    }

    const std::vector<GbirBasicBlock*>&
    Dominance::frontier_get(GbirBasicBlock* block) const
    {
        return frontier_.at(block);
    }
} // namespace gbir
