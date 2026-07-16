#include <gbir-opti/dead-block.h>
#include <gbir-opti/dead-code-elimination.h>
#include <gbir-opti/mem2reg.h>
#include <gbir-opti/pipeline.h>
#include <gbir/top-level.h>

namespace gbir
{
    static void optimize_cfg(std::vector<std::unique_ptr<GbirBasicBlock>>& blocks,
                             int& next_value_id)
    {
        DeadBlockElimination().run(blocks);
        Mem2Reg().run(blocks, next_value_id);
        DeadCodeElimination().run(blocks);
    }

    void optimize(GbirModule& module)
    {
        for (auto& top_level : module.top_levels_get())
        {
            if (auto* func = dynamic_cast<GbirFunction*>(top_level.get()))
            {
                int next_value_id = func->next_value_id_get();
                optimize_cfg(func->blocks_get(), next_value_id);
                func->next_value_id_set(next_value_id);
            }
            else if (auto* scene = dynamic_cast<GbirScene*>(top_level.get()))
            {
                int next_value_id = scene->next_value_id_get();
                optimize_cfg(scene->precondition_get(), next_value_id);
                optimize_cfg(scene->blocks_get(), next_value_id);
                scene->next_value_id_set(next_value_id);
            }
        }
    }
} // namespace gbir
