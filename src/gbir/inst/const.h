#pragma once
#include <gbir/inst/inst.h>
#include <gbir/value.h>

namespace gbir
{
    class ConstInst : public GbirInst
    {
    public:
        explicit ConstInst(GbirValue result);
        GbirValue result_get() const;
        void result_set(GbirValue result);

    private:
        GbirValue result_;
    };

    class ConstIntInst : public ConstInst
    {
    public:
        ConstIntInst(int raw_value, GbirValue result);
        void accept(GbirVisitorBase& v) override;
        int raw_value_get() const;
        void raw_value_set(int raw_value);

    private:
        int raw_value_;
    };

    class ConstFloatInst : public ConstInst
    {
    public:
        ConstFloatInst(float raw_value, GbirValue result);
        void accept(GbirVisitorBase& v) override;
        float raw_value_get() const;
        void raw_value_set(float raw_value);

    private:
        float raw_value_;
    };

    class ConstStringInst : public ConstInst
    {
    public:
        ConstStringInst(std::string raw_value, GbirValue result);
        void accept(GbirVisitorBase& v) override;
        std::string raw_value_get() const;
        void raw_value_set(std::string raw_value);

    private:
        std::string raw_value_;
    };

    class ConstBoolInst : public ConstInst
    {
    public:
        ConstBoolInst(bool raw_value, GbirValue result);
        void accept(GbirVisitorBase& v) override;
        bool raw_value_get() const;
        void raw_value_set(bool raw_value);

    private:
        bool raw_value_;
    };

    class ConstDollarsInst : public ConstIntInst
    {
    public:
        ConstDollarsInst(int raw_value, GbirValue result);
        void accept(GbirVisitorBase& v) override;
    };

    class ConstChanceInst : public ConstIntInst
    {
    public:
        ConstChanceInst(int raw_value, GbirValue result);
        void accept(GbirVisitorBase& v) override;
    };

    class ConstStreakInst : public ConstIntInst
    {
    public:
        ConstStreakInst(int raw_value, GbirValue result);
        void accept(GbirVisitorBase& v) override;
    };
} // namespace gbir
