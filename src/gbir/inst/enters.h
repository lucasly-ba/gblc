#pragma once
#include <gbir/inst/inst.h>
#include <string>

namespace gbir
{
    class EnterInst : public GbirInst
    {
    public:
        EnterInst(std::string player_name, std::string scene_name);
        void accept(GbirVisitorBase& v) override;

        const std::string& player_name_get() const;
        void player_name_set(std::string player_name);
        const std::string& scene_name_get() const;
        void scene_name_set(std::string scene_name);

    private:
        std::string player_name_;
        std::string scene_name_;
    };

} // namespace gbir
