#include <ast/type.h>

namespace ast
{
    std::string to_string(Type type)
    {
        switch (type)
        {
        case Type::Int:
            return "int";
        case Type::Float:
            return "float";
        case Type::String:
            return "string";
        case Type::Bool:
            return "bool";
        case Type::Dollar:
            return "dollar";
        case Type::Chance:
            return "chance";
        case Type::Reputation:
            return "reputation";
        }
        return "unknown";
    }
} // namespace ast
