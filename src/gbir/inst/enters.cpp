#include <gbir/inst/enters.h>

namespace gbir
{
    EnterInst::EnterInst(std::string player_name, std::string scene_name)
        : player_name_(std::move(player_name))
        , scene_name_(std::move(scene_name))
    {}

    void EnterInst::accept(GbirVisitorBase& v)
    {
        v.visit(*this);
    }

    const std::string& EnterInst::player_name_get() const
    {
        return player_name_;
    }

    void EnterInst::player_name_set(std::string player_name)
    {
        player_name_ = std::move(player_name);
    }

    const std::string& EnterInst::scene_name_get() const
    {
        return scene_name_;
    }

    void EnterInst::scene_name_set(std::string scene_name)
    {
        scene_name_ = std::move(scene_name);
    }

} // namespace gbir
