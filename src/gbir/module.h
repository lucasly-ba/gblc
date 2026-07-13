#pragma once
#include <gbir/top-level.h>
#include <memory>
#include <vector>

namespace gbir
{
    class GbirModule
    {
    public:
        GbirModule() = default;

        const std::vector<std::unique_ptr<GbirTopLevel>>&
        top_levels_get() const;
        std::vector<std::unique_ptr<GbirTopLevel>>& top_levels_get();
        void add_top_level(std::unique_ptr<GbirTopLevel> top_level);

    private:
        std::vector<std::unique_ptr<GbirTopLevel>> top_levels_;
    };
} // namespace gbir
