#include <gbir/inst/scene.h>

namespace gbir
{
    StartInst::StartInst(std::string scene_name)
        : scene_name_(std::move(scene_name))
    {}

    void StartInst::accept(GbirVisitorBase& v)
    {
        v.visit(*this);
    }

    const std::string& StartInst::scene_name_get() const
    {
        return scene_name_;
    }

    void StartInst::scene_name_set(std::string scene_name)
    {
        scene_name_ = std::move(scene_name);
    }
} // namespace gbir
