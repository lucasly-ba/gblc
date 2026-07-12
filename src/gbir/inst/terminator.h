#pragma once
#include <gbir/basic-block.h>
#include <gbir/inst/inst.h>
#include <gbir/value.h>

namespace gbir
{
    class CondBranchInst : public GbirInst
    {
    public:
        CondBranchInst(GbirValue condition, GbirBasicBlock* then_bb,
                       GbirBasicBlock* else_bb);
        void accept(GbirVisitorBase& v) override;

        GbirValue condition_get() const;
        void condition_set(GbirValue condition);
        GbirBasicBlock* then_bb_get() const;
        void then_bb_set(GbirBasicBlock* then_bb);
        GbirBasicBlock* else_bb_get() const;
        void else_bb_set(GbirBasicBlock* else_bb);

    private:
        GbirValue condition_;
        GbirBasicBlock* then_bb_;
        GbirBasicBlock* else_bb_;
    };

    class BranchInst : public GbirInst
    {
    public:
        explicit BranchInst(GbirBasicBlock* target_bb);
        void accept(GbirVisitorBase& v) override;

        GbirBasicBlock* target_bb_get() const;
        void target_bb_set(GbirBasicBlock* target_bb);

    private:
        GbirBasicBlock* target_bb_;
    };

    class ReturnInst : public GbirInst
    {
    public:
        explicit ReturnInst(GbirValue value);
        void accept(GbirVisitorBase& v) override;

        GbirValue value_get() const;
        void value_set(GbirValue value);

    private:
        GbirValue value_;
    };
} // namespace gbir
