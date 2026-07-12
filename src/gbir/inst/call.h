#pragma once
#include <gbir/inst/inst.h>
#include <gbir/value.h>
#include <string>
#include <vector>

namespace gbir
{
    class CallInst : public GbirInst
    {
    public:
        CallInst(std::string name, std::vector<GbirValue> args,
                 GbirValue result);
        void accept(GbirVisitorBase& v) override;

        const std::string& name_get() const;
        void name_set(std::string name);

        const std::vector<GbirValue>& args_get() const;
        std::vector<GbirValue>& args_get();
        void args_set(std::vector<GbirValue> args);

        GbirValue result_get() const;
        void result_set(GbirValue result);

    private:
        std::string name_;
        std::vector<GbirValue> args_;
        GbirValue result_;
    };
} // namespace gbir
