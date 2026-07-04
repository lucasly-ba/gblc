#include <ast.h>
#include <ast/dec.h>

namespace ast
{

    const Location& Ast::location_get() const
    {
        return location_;
    }

    void Ast::location_set(const Location& location)
    {
        location_ = location;
    }

    const std::vector<dec_ptr>& Program::decs_get() const
    {
        return decs_;
    }
    std::vector<dec_ptr>& Program::decs_get()
    {
        return decs_;
    }
    void Program::decs_set(std::vector<dec_ptr> decs)
    {
        decs_ = std::move(decs);
    }

} // namespace ast
