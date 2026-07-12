#pragma once
#include <gbir/basic-block.h>
#include <gbir/inst/inst.h>
#include <gbir/value.h>
#include <utility>
#include <vector>

namespace gbir
{
    class PhiInst : public GbirInst
    {
    public:
        PhiInst(GbirValue result,
                std::vector<std::pair<GbirValue, GbirBasicBlock*>> incoming);
        void accept(GbirVisitorBase& v) override;

        GbirValue result_get() const;
        void result_set(GbirValue result);

        const std::vector<std::pair<GbirValue, GbirBasicBlock*>>&
        incoming_get() const;
        void incoming_set(
            std::vector<std::pair<GbirValue, GbirBasicBlock*>> incoming);
        void add_incoming(GbirValue value, GbirBasicBlock* from_block);

    private:
        GbirValue result_;
        std::vector<std::pair<GbirValue, GbirBasicBlock*>> incoming_;
    };
} // namespace gbir
