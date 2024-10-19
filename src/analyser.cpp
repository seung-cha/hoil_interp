#include "analyser.h"
#include <memory>
using namespace ASTs;

Analyser::Analyser(Program *program) : program{program}
{
    symbolTable.OpenScope();
    program->Visit(this, nullptr);
    symbolTable.CloseScope();

    if(symbolTable.level != -1)
    {
        std::cout << "Symbol Table level is not -1 after termination?" << std::endl;
        std::cout << "Level: " << symbolTable.level << std::endl;
    }
}

AST *Analyser::VisitProgram(Program *program, AST *obj)
{
    return program->Visit(this, obj);
}

AST *Analyser::VisitFuncDecl(FuncDecl *decl, AST *obj)
{
    symbolTable.Insert(decl->identifier->spelling, decl);
    return nullptr;
}

AST *Analyser::VisitVarDecl(VarDecl *decl, AST *obj)
{
    // Iterate through decl expr and map idents to this
    VarDeclList *list = dynamic_cast<VarDeclList*>(decl->list.get());

    if(!list)
    {
        std::cerr << "Downcasting failed on VarDeclList?" << std::endl;
        exit(1);
    }

    for(VarDeclList *ptr = list; ptr; ptr = dynamic_cast<VarDeclList*>(ptr->next.get()))
    {
        VarDeclExpr *expr = dynamic_cast<VarDeclExpr*>(ptr->expr.get());
        if(!expr)
        {
            std::cerr << "Downcasting failed on VarDelExpr?" << std::endl;
            exit(1);
        }

        symbolTable.Insert(expr->identifier->spelling, decl);
    }

    return nullptr;
}



