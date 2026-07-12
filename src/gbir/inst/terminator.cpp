#include <gbir/inst/terminator.h>

namespace gbir
{
    CondBranchInst::CondBranchInst(GbirValue condition, GbirBasicBlock* then_bb,
                                   GbirBasicBlock* else_bb)
        : condition_(condition)
        , then_bb_(then_bb)
        , else_bb_(else_bb)
    {}

    void CondBranchInst::accept(GbirVisitorBase& v)
    {
        v.visit(*this);
    }

    GbirValue CondBranchInst::condition_get() const
    {
        return condition_;
    }

    void CondBranchInst::condition_set(GbirValue condition)
    {
        condition_ = condition;
    }

    GbirBasicBlock* CondBranchInst::then_bb_get() const
    {
        return then_bb_;
    }

    void CondBranchInst::then_bb_set(GbirBasicBlock* then_bb)
    {
        then_bb_ = then_bb;
    }

    GbirBasicBlock* CondBranchInst::else_bb_get() const
    {
        return else_bb_;
    }

    void CondBranchInst::else_bb_set(GbirBasicBlock* else_bb)
    {
        else_bb_ = else_bb;
    }

    BranchInst::BranchInst(GbirBasicBlock* target_bb)
        : target_bb_(target_bb)
    {}

    void BranchInst::accept(GbirVisitorBase& v)
    {
        v.visit(*this);
    }

    GbirBasicBlock* BranchInst::target_bb_get() const
    {
        return target_bb_;
    }

    void BranchInst::target_bb_set(GbirBasicBlock* target_bb)
    {
        target_bb_ = target_bb;
    }

    ReturnInst::ReturnInst(GbirValue value)
        : value_(value)
    {}

    void ReturnInst::accept(GbirVisitorBase& v)
    {
        v.visit(*this);
    }

    GbirValue ReturnInst::value_get() const
    {
        return value_;
    }

    void ReturnInst::value_set(GbirValue value)
    {
        value_ = value;
    }
} // namespace gbir
