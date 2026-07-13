#include <gbir/module.h>

namespace gbir
{
    const std::vector<std::unique_ptr<GbirTopLevel>>&
    GbirModule::top_levels_get() const
    {
        return top_levels_;
    }

    std::vector<std::unique_ptr<GbirTopLevel>>& GbirModule::top_levels_get()
    {
        return top_levels_;
    }

    void GbirModule::add_top_level(std::unique_ptr<GbirTopLevel> top_level)
    {
        top_levels_.push_back(std::move(top_level));
    }
} // namespace gbir
