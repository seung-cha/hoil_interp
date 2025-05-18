#include "compiler.h"
#include <cstring>
#include <iostream>
#include <fstream>
#include <memory>
#include "scanner.h"
#include "lexer.h"
#include "parser.h"
#include "analyser.h"
#include "AST.h"
#include "codegen.h"

Compiler::Compiler(char *source, int argc, char **argv): source{source}, argc{argc}, argv{argv}
{

}

Compiler::~Compiler()
{

}

bool Compiler::Run()
{
    bool lexer_verbose = false;
    bool test_lexer = false;
    bool test_parser = false;
    bool test_analyser = false;
    bool draw_ast = false;

    for(int i = 3; i < argc; i++)
    {
        char const* str = argv[i];
        // Print help
        if(strcmp(str, "--help") == 0 || strcmp(str, "-h") == 0)
        {
            std::cout << "\n\nUsage: " << argv[0] << 
            " [source_file] --flags\n" 
            "--flags can be any of the following:\n\n"
            "--lexer-verbose    Print lexemes obtained by lexer\n"
            "--test-lexer           Terminate after lexer. Fail on obtaining error lexeme.\n"
            "--test-parser       Terminate after parser. Fail if source file is syntactically ill-formed\n"
            "--test-analyser      Terminate after analyser. Fail if source file is semantically ill-formed\n"
            "--ast          Print Abstract Syntax Tree"<< std::endl;

            return true;
        }

        if(strcmp(str, "--lexer-verbose") == 0)
        {
            lexer_verbose = true;
        }
        else if(strcmp(str, "--test-lexer") == 0)
        {
            test_lexer = true;
        }
        else if(strcmp(str, "--test-parser") == 0)
        {
            test_parser = true;
        }
        else if(strcmp(str, "--ast") == 0)
        {
            draw_ast = true;
        }
    }

    Scanner scanner{argv[1]};

    if(!scanner.IsReady())
    {
        std::cout << "Scanner failed to open the file.\n";
        return false;
    }


    Lexer lexer{&scanner};
    Lexicons::Lexicon *lex = nullptr;

    if(lexer_verbose)
    {
        lexer.Verbose();
    }

    const auto lexemes = lexer.Lexemes();

    for(auto& lexeme : lexemes)
    {
        if(lexeme->Id == Lexicons::Lexicon::ERR)
        {
            std::cout << "Error lexeme detected!" << std::endl;
            std::cout << lexeme->Verbose() << std::endl;
            return false;
        }
    }

    if(test_lexer)
    {
        return true;
    }


    Parser parser{&lexer};

    for(const auto& str : parser.ErrorMsgs())
    {
        std::cout << str << std::endl;
    }

    if(parser.ErrorMsgs().size() > 0)
    {
        return false;
    }


    if(test_parser)
    {
        return true;
    }


    Analyser analyser{parser.program.get(), reservedFuncs};

    if(draw_ast)
    {
        parser.program->Print(0);   
    }

    if(analyser.errorMsgs.size() != 0)
    {
        for(auto& msg : analyser.errorMsgs)
        {
            std::cout << msg << std::endl;
        }

        return false;
    }
    

    if(test_analyser)
    {
        return true;
    }

    CodeGen gen{parser.program.get()};

    // Write to file
    std::ofstream outStream{argv[2]};
    outStream << gen.bytecode;  
    // std::cout << gen.bytecode << std::endl;

    return true;
}

void Compiler::ReserveFunc(ASTs::VarType type, std::string decl, std::vector<ASTs::VarType> params, std::vector<std::string> paramIdent)
{
    ASTs::Identifier *funcIdent = new ASTs::Identifier(decl, 0, 0);
    ASTs::List *funcList = nullptr;
    ASTs::Type *funcType = MakeType(type);

    if(params.size() != 0)
    {
        ASTs::ParamList *list = new ASTs::ParamList{nullptr, nullptr};
        ASTs::ParamList *head = nullptr;
        for(int i = 0; i < params.size(); i++)
        {
            ASTs::Type *paramType = nullptr;

            if(head == nullptr)
            {
                head = list;
            }
            else
            {
                ASTs::ParamList *temp = new ASTs::ParamList(nullptr, nullptr);
                head->next = std::unique_ptr<ASTs::ParamList>{temp};
                head = temp;
            }

            paramType = MakeType(params[i]);

            ASTs::Identifier *ident = new ASTs::Identifier(paramIdent[i], 0, 0);
            ASTs::Param *param = new ASTs::Param(paramType, ident, 0, 0);

            head->param = std::unique_ptr<ASTs::Param>{param};
        }
        head->next = std::make_unique<ASTs::EmptyParamList>();
        funcList = list;
    }
    else
    {
        funcList = new ASTs::EmptyParamList();
    }


    reservedFuncs.push_back(std::make_unique<ASTs::FuncDecl>(funcType, funcIdent, funcList, new ASTs::EmptyStmt(0, 0), 0, 0));
    reservedFuncs[reservedFuncs.size() - 1]->isFuncDecl = true;


}

ASTs::Type *Compiler::MakeType(ASTs::VarType type)
{
    switch(type)
    {
        case ASTs::VarType::INT:
        return new ASTs::IntType(0, 0);
        break;
        case ASTs::VarType::REAL:
        return new ASTs::RealType(0, 0);
        break;
        case ASTs::VarType::BOOL:
        return new ASTs::BoolType(0, 0);
        break;
        case ASTs::VarType::STRING:
        return new ASTs::StringType(0, 0);
        break;
        case ASTs::VarType::VOID:
        return new ASTs::VoidType(0, 0);
    }

    assert(false && "MakeType() couldn't handle type at switch block");
}