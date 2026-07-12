#include <gbir/inst/phi.h>

namespace gbir
{
    PhiInst::PhiInst(
        GbirValue result,
        std::vector<std::pair<GbirValue, GbirBasicBlock*>> incoming)
        : result_(result)
        , incoming_(std::move(incoming))
    {}

    void PhiInst::accept(GbirVisitorBase& v)
    {
        v.visit(*this);
    }

    GbirValue PhiInst::result_get() const
    {
        return result_;
    }

    void PhiInst::result_set(GbirValue result)
    {
        result_ = result;
    }

    const std::vector<std::pair<GbirValue, GbirBasicBlock*>>&
    PhiInst::incoming_get() const
    {
        return incoming_;
    }

    void PhiInst::incoming_set(
        std::vector<std::pair<GbirValue, GbirBasicBlock*>> incoming)
    {
        incoming_ = std::move(incoming);
    }

    void PhiInst::add_incoming(GbirValue value, GbirBasicBlock* from_block)
    {
        incoming_.push_back({ value, from_block });
    }
} // namespace gbir
