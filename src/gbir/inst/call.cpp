#include <gbir/inst/call.h>

namespace gbir
{
    CallInst::CallInst(std::string name, std::vector<GbirValue> args,
                       GbirValue result)
        : name_(std::move(name))
        , args_(std::move(args))
        , result_(result)
    {}

    void CallInst::accept(GbirVisitorBase& v)
    {
        v.visit(*this);
    }

    const std::string& CallInst::name_get() const
    {
        return name_;
    }

    void CallInst::name_set(std::string name)
    {
        name_ = std::move(name);
    }

    const std::vector<GbirValue>& CallInst::args_get() const
    {
        return args_;
    }

    std::vector<GbirValue>& CallInst::args_get()
    {
        return args_;
    }

    void CallInst::args_set(std::vector<GbirValue> args)
    {
        args_ = std::move(args);
    }

    GbirValue CallInst::result_get() const
    {
        return result_;
    }

    void CallInst::result_set(GbirValue result)
    {
        result_ = result;
    }
} // namespace gbir
