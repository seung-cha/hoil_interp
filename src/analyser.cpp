#include "analyser.h"
#include <memory>
#include <sstream>

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

// Decls
AST *Analyser::VisitFuncDecl(FuncDecl *decl, AST *obj)
{
    if(!symbolTable.Insert(decl->identifier->spelling, decl))
    {
        std::stringstream ss;
        ss << "Function is already declared: " << decl->identifier->spelling;
        ReportError(ss.str());
    }

    decl->stmt->Visit(this, nullptr);
    return nullptr;
}

AST *Analyser::VisitVarDecl(VarDecl *decl, AST *obj)
{
    if(!symbolTable.Insert(decl->identifier->spelling, decl))
    {
        std::stringstream ss;
        ss << "Variable is already declared: " << decl->identifier->spelling;
        ReportError(ss.str());
    }

    // TODO: Check LHS, RHS compatibility


    return nullptr;
}

AST *Analyser::VisitVarDeclExpr(VarDeclExpr *expr, AST *obj)
{
    // Visit underlying expr, return type
    expr->expr->Visit(this, nullptr);
    expr->type = std::move(expr->expr->type->DeepCopy());

    return expr->type.get();
}

AST *Analyser::VisitVarDeclList(VarDeclList *list, AST *obj)
{
    list->decl->Visit(this, nullptr);
    list->next->Visit(this, nullptr);
    return nullptr;
}

// Exprs
AST *Analyser::VisitAssignExpr(AssignExpr *expr, AST *obj)
{
    expr->lhs->Visit(this, nullptr);
    expr->rhs->Visit(this, nullptr);

    if(!expr->op->Compatible(expr->lhs->type.get(), expr->rhs->type.get()))
    {
        ReportError("Assignment Expression Type is Incompatible!");
        expr->type = std::make_unique<ErrorType>();
    }
    else
    {
        expr->type = expr->lhs->type->DeepCopy();
    }

    return expr->type.get();
}

AST *Analyser::VisitBinaryExpr(BinaryExpr *expr, AST *obj)
{
    expr->lhs->Visit(this, nullptr);
    expr->rhs->Visit(this, nullptr);

    if(!expr->op->Compatible(expr->lhs->type.get(), expr->rhs->type.get()))
    {
        ReportError("Assignment Expression Type is Incompatible!");
        expr->type = std::make_unique<ErrorType>();
    }
    else
    {
        if(expr->op->IsBoolOp())
        {
            expr->type = std::make_unique<BoolType>();
        }
        else
        {
            expr->type = expr->lhs->type->DeepCopy();
        }
    }

    return expr->type.get();
}

AST *Analyser::VisitBoolExpr(BoolExpr *expr, AST *obj)
{
    expr->type = std::make_unique<BoolType>();
    return expr->type.get();
}

AST *Analyser::VisitEmptyExpr(EmptyExpr *expr, AST *obj)
{
    return nullptr;
}

AST *Analyser::VisitErrorExpr(ErrorExpr *expr, AST *obj)
{
    return nullptr;
}

AST *Analyser::VisitFuncCallExpr(FunctionCallExpr *expr, AST *obj)
{
    //TODO
    return nullptr;
}

AST *Analyser::VisitIntExpr(IntExpr *expr, AST *obj)
{
    expr->type = std::make_unique<IntType>();
    return expr->type.get();
}

AST *Analyser::VisitPostUnaryExpr(PostUnaryExpr *expr, AST *obj)
{
    // TODO: Make sure expr is a variable
    if(!expr->op->Compatible(expr->expr->type.get(), nullptr))
    {
        ReportError("Unary Expression Type is incompatible!");
        expr->type = std::make_unique<ErrorType>();
    }
    else
    {
        if(expr->op->IsBoolOp())
        {
            expr->type = std::make_unique<BoolType>();
        }
        else
        {
            expr->type = expr->expr->type->DeepCopy();
        }
    }

    return expr->type.get();
}

AST *Analyser::VisitPreUnaryExpr(PreUnaryExpr *expr, AST *obj)
{
    // TODO: Make sure expr is a variable
    if(!expr->op->Compatible(expr->expr->type.get(), nullptr))
    {
        ReportError("Unary Expression Type is incompatible!");
        expr->type = std::make_unique<ErrorType>();
    }
    else
    {
        if(expr->op->IsBoolOp())
        {
            expr->type = std::make_unique<BoolType>();
        }
        else
        {
            expr->type = expr->expr->type->DeepCopy();
        }
    }

    return expr->type.get();
}

AST *Analyser::VisitRealExpr(RealExpr *expr, AST *obj)
{
    expr->type = std::make_unique<RealType>();
    return expr->type.get();
}

AST *Analyser::VisitStringExpr(StringExpr *expr, AST *obj)
{
    expr->type = std::make_unique<StringType>();
    return expr->type.get();
}

AST *Analyser::VisitVarExpr(VariableExpr *expr, AST *obj)
{
    // TODO
    return nullptr;
}











