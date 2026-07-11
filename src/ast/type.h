#pragma once
#include <optional>
#include <string>

namespace ast
{
    enum class Type
    {
        Int,
        Float,
        String,
        Bool,
        Dollars,
        Chance,
        Streak,
        Void,
    };

    std::optional<Type> get_type(const std::string& value);

    std::string to_string(Type type);
} // namespace ast
