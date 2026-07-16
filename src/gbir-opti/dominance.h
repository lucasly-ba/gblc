#pragma once
#include <gbir/basic-block.h>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <vector>

namespace gbir
{
    class Dominance
    {
    public:
        void compute(std::vector<std::unique_ptr<GbirBasicBlock>>& blocks);

        GbirBasicBlock* idom_get(GbirBasicBlock* block);

        const std::vector<GbirBasicBlock*>&
        frontier_get(GbirBasicBlock* block) const;

    private:
        void dfs_postorder(GbirBasicBlock* block);

        void compute_idoms(GbirBasicBlock* entry);
        GbirBasicBlock* intersect(GbirBasicBlock* a, GbirBasicBlock* b);

        void compute_frontiers();

        std::vector<GbirBasicBlock*> postorder_;
        std::unordered_map<GbirBasicBlock*, int> po_num_;
        std::unordered_set<GbirBasicBlock*> visited_;
        std::unordered_map<GbirBasicBlock*, GbirBasicBlock*> idom_;
        std::unordered_map<GbirBasicBlock*, std::vector<GbirBasicBlock*>>
            frontier_;

        int next_po_num = 0;
    };
} // namespace gbir
