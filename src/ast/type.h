#pragma once
#include <string>

namespace ast
{
    enum class Type
    {
        Int,
        Float,
        String,
        Bool,
        Dollar,
        Chance,
        Reputation,
    };

    std::string to_string(Type type);
} // namespace ast
