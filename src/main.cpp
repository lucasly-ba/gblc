#include <CLI/CLI.hpp>
#include <bind/binder.h>
#include <fstream>
#include <gbir-gen/gbir-gen.h>
#include <gbir-opti/pipeline.h>
#include <gbir/print-gbir.h>
#include <iostream>
#include <parse/lexer.h>
#include <parse/parser.h>
#include <ast/print-ast.h>
#include <sstream>
#include <type/type-checker.h>

int main(int argc, char* argv[])
{
    CLI::App app{ "gblc compiler" };

    std::string input_file;
    bool lex_trace = false;
    bool print_ast = false;
    bool print_gbir = false;
    bool bindings = false;
    bool opti = false;

    app.add_option("file", input_file, "Input .gblc file")->required();
    app.add_flag("--lex-trace", lex_trace, "Trace the lexer");
    app.add_flag("--print-ast", print_ast, "Pretty-print the AST");
    app.add_flag("--print-gbir", print_gbir, "Pretty-print the GBIR");
    app.add_flag("--opti", opti, "Run the GBIR optimization pipeline");
    app.add_flag("--bindings", bindings,
                 "Annotate --print-ast names with their resolved definitions");

    CLI11_PARSE(app, argc, argv);

    std::ifstream f(input_file);
    std::ostringstream ss;
    ss << f.rdbuf();
    std::string content = ss.str();

    parser::Lexer lex(lex_trace, content);
    auto tokens = lex.lex_tokens();

    if (lex.has_error())
    {
        for (auto& err : lex.get_errors())
            std::cerr << "error: " << err.message << " at " << err.line << ":"
                      << err.col << "\n";
        return 1;
    }

    parser::Parser parser(tokens);
    ast::Program program = parser.parse_program();
    if (parser.has_error())
    {
        for (auto& err : parser.get_errors())
            std::cerr << "error: " << err.message << " at " << err.line << ":"
                      << err.col << "\n";
        return 2;
    }

    if (!print_ast || bindings || print_gbir)
    {
        bind::Binder binder;
        binder.bind_program(program);
        if (binder.has_error())
        {
            for (auto& err : binder.get_errors())
                std::cerr << "error: " << err.message << " at "
                          << err.location.line << ":" << err.location.col
                          << "\n";
            return 3;
        }

        type::TypeChecker typechecker;
        typechecker.typecheck_program(program);
        if (typechecker.has_error())
        {
            for (auto& err : typechecker.get_errors())
                std::cerr << "error: " << err.message << " at "
                          << err.location.line << ":" << err.location.col
                          << "\n";
            return 4;
        }
    }

    if (print_ast)
    {
        ast::PrintAst ast_printer(std::cout, bindings);
        for (auto& dec : program.decs_get())
            dec->accept(ast_printer);
    }

    if (print_gbir)
    {
        gbir::GbirGen gbir_gen;
        gbir_gen.generate_gbir(program);
        if (opti)
            gbir::optimize(gbir_gen.module_get());
        gbir::PrintGbir gbir_printer(std::cout);
        gbir_printer.print(gbir_gen.module_get());
    }
}
