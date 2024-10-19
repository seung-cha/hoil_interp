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
    decl->stmt->Visit(this, nullptr);
    return nullptr;
}

AST *Analyser::VisitVarDecl(VarDecl *decl, AST *obj)
{
    decl->list->Visit(this, decl);
    return nullptr;
}

AST *Analyser::VisitVarDeclList(VarDeclList *list, AST *obj)
{
    list->expr->Visit(this, obj);
    list->next->Visit(this, obj);
    return nullptr;
}

AST *Analyser::VisitVarDeclExpr(VarDeclExpr *expr, AST *obj)
{
    
}



