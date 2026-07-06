#include <ast/all.h>
#include <factory.h>
#include <optional>
#include <parser.h>
#include <set>
#include <token.h>
#include <type.h>

namespace parser
{
    using namespace ast;

    Parser::Parser(bool trace, std::vector<Token> tokens)
        : trace_(trace)
        , tokens_(tokens)
    {}

    Program Parser::parse_program()
    {
        std::vector<dec_ptr> decs{};
        while (!is_eof())
        {
            switch (cur().kind)
            {
            case TokenKind::Var:
                decs.push_back(parse_var_dec());
                break;
            case TokenKind::Function:
                decs.push_back(parse_function_dec());
                break;
            case TokenKind::Scene:
                decs.push_back(parse_scene_dec());
                break;
            case TokenKind::Player:
                decs.push_back(parse_player_dec());
                break;
            default:
                emit_error("Only declarations are allowed in top level");
                walk();
            }
        }
        return Program(std::move(decs));
    }

    dec_ptr Parser::parse_var_dec()
    {
        Location location = get_location();
        walk();
        std::string name;
        std::optional<Type> type = std::nullopt;
        if (kind() != TokenKind::ID)
            return fail("Expected name after `var`");
        name = value();
        walk();
        if (kind() == TokenKind::Colon)
        {
            walk();
            type = get_type(value());
            if (!type.has_value())
                return fail("Unexpected type name");
            walk();
        }
        if (kind() == TokenKind::Eq)
        {
            walk();
            exp_ptr init = parse_exp();
            if (type.has_value())
                return make_VarDec(location, std::move(name), *type,
                                   std::move(init));
            return make_VarDec(location, std::move(name), std::move(init));
        }
        else
            return fail("expected ':' or '=' after var name");
    }

    bool Parser::parse_function_args(std::vector<std::unique_ptr<VarDec>>& args)
    {
        if (kind() != TokenKind::LPar)
            return emit_and_synchronize(
                "Expected left parenthesis after function name");
        walk();
        while (!is_eof() && kind() != TokenKind::RPar)
        {
            if (kind() != TokenKind::ID)
                return emit_and_synchronize("Expected var name");
            std::string name = value();
            Location loc = get_location();
            walk();
            if (kind() != TokenKind::Colon)
                return emit_and_synchronize("Expected colon after var name");
            walk();
            auto type = get_type(value());
            if (!type.has_value())
                return emit_and_synchronize("Unexpected type name");
            args.push_back(make_var_dec_typed(loc, name, *type));
            walk();
            if (kind() == TokenKind::Comma)
                walk();
            else if (kind() != TokenKind::RPar)
                return emit_and_synchronize(
                    "Expected ',' or ')' after parameter");
        }
        walk();

        return true;
    }

    dec_ptr Parser::parse_function_dec()
    {
        Location location = get_location();
        walk();
        std::string name;
        std::optional<Type> type = std::nullopt;
        std::vector<std::unique_ptr<VarDec>> args;
        std::vector<ast::stmt_ptr> body;

        if (kind() != TokenKind::ID)
            return fail("Expected name after `fn`");
        name = value();
        walk();
        if (parse_function_args(args) == false)
            return nullptr;
        if (kind() == TokenKind::Arrow)
        {
            walk();
            type = get_type(value());
            if (!type.has_value())
                return fail("Unexpected type name");
            walk();
        }
        if (kind() != TokenKind::LBrace)
            return fail("Expected left bracket in function declaration");
        walk();
        body = parse_body();

        if (kind() != TokenKind::RBrace)
            return fail("Expected right bracket in function declaration");
        if (type.has_value())
            return make_FuncDec(location, name, std::move(args), *type,
                                std::move(body));
        return make_FuncDec(location, name, std::move(args), std::move(body));
    }

    dec_ptr Parser::parse_scene_dec()
    {}

    bool Parser::parse_player_field(std::set<TokenKind>& player_fields,
                                    TokenKind field, int& val, Location& loc,
                                    TokenKind lit)
    {
        if (player_fields.find(field) == player_fields.end())
            return emit_and_synchronize("Field specified twice");
        walk();
        if (kind() != TokenKind::Colon)
            return emit_and_synchronize("Expected colon after field");
        walk();
        if (kind() != lit)
            return emit_and_synchronize("Expected value after field");
        loc = get_location();
        val = std::stoi(value().substr(0, value().size() - 1));
        player_fields.erase(field);
        return true;
    }

    dec_ptr Parser::parse_player_dec()
    {
        Location location = get_location();
        walk();
        std::string name;
        int dollars;
        int chance;
        int reputation;
        Location dollars_location;
        Location chance_location;
        Location reputation_location;

        if (kind() != TokenKind::ID)
            return fail("Expected name after `player`");
        name = value();
        walk();
        if (kind() != TokenKind::LBrace)
            return fail("Expected left bracket after player name");
        walk();
        std::set player_fields{ TokenKind::Dollars, TokenKind::Chance,
                                TokenKind::Reputation };

        while (!player_fields.empty())
        {
            TokenKind field = kind();
            switch (kind())
            {
            case TokenKind::Dollars:
                if (!parse_player_field(player_fields, field, dollars,
                                        dollars_location,
                                        TokenKind::DollarsLit))
                    return nullptr;
                break;
            case TokenKind::Chance:
                if (!parse_player_field(player_fields, field, chance,
                                        chance_location, TokenKind::ChanceLit))
                    return nullptr;
                break;
            case TokenKind::Reputation:
                if (!parse_player_field(player_fields, field, reputation,
                                        reputation_location,
                                        TokenKind::ReputationLit))
                    return nullptr;
                break;
            default:
                return fail("Unrecognized field");
            }
            walk();
            if (!player_fields.empty())
            {
                if (kind() != TokenKind::Comma)
                    return fail("Expected comma after field");
                walk();
            }
        }

        if (kind() != TokenKind::RBrace)
            return fail("Expected right bracket after player fields");
        walk();
        return make_PlayerDec(
            location, std::move(name),
            make_DollarsExp(dollars_location, dollars),
            make_ChanceExp(chance_location, chance),
            make_ReputationExp(reputation_location, reputation));
    }

} // namespace parser
