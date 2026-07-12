#pragma once
#include <gbir/inst/inst.h>
#include <string>

namespace gbir
{
    class StartInst : public GbirInst
    {
    public:
        explicit StartInst(std::string scene_name);
        void accept(GbirVisitorBase& v) override;

        const std::string& scene_name_get() const;
        void scene_name_set(std::string scene_name);

    private:
        std::string scene_name_;
    };
} // namespace gbir
