#include "codegen.h"

using namespace ASTs;

CodeGen::CodeGen(Program *program, std::vector<std::unique_ptr<ASTs::FuncDecl>> &reserve) : program{program}
{
    program->Visit(this, nullptr);
    bytecode = ss.str();
}

CodeGen::CodeGen(Program *program) : program{program}
{
    program->Visit(this, nullptr);
    bytecode = ss.str();
}


// Decls
AST *CodeGen::VisitFuncDecl(FuncDecl *decl, AST *obj)
{
    ss << "$func_decl ";
    decl->identifier->Visit(this, nullptr);
    ss << ' ';
    decl->type->Visit(this, nullptr);
    ss << ' ';
    ss << "$param ";
    decl ->params->Visit(this, nullptr);
    ss << '\n';
    decl->stmt->Visit(this, nullptr);
    ss << "$func_decl_end";
    return nullptr;
}

AST *CodeGen::VisitFuncDeclList(FuncDeclList *list, AST *obj)
{
    return nullptr;
}

AST *CodeGen::VisitArrDecl(ArrDecl *decl, AST *obj)
{
    ss << "$insert ";
    decl->identifier->Visit(this, nullptr);
    ss << ' ';
    decl->index->Visit(this, nullptr);
    ss << ' ';
    decl->expr->Visit(this, nullptr);
    return nullptr;
}

AST *CodeGen::VisitVarDecl(VarDecl *decl, AST *obj)
{
    // Write $decl %ident type
    ss << "$decl ";
    decl->identifier->Visit(this, nullptr);
    ss << " ";

    // If void type, print as flex so GPT can know
    if(decl->type->IsVoidType())
    {
        ss << "$flex";
    }
    else
    {
        decl->type->Visit(this, nullptr);
    }
    ss << " ";
    decl->expr->Visit(this, nullptr);

    return nullptr;
}

AST *CodeGen::VisitVarDeclExpr(VarDeclExpr *expr, AST *obj)
{
    return nullptr;
}

// Exprs
AST *CodeGen::VisitAssignExpr(AssignExpr *expr, AST *obj)
{
    return nullptr;
}

AST *CodeGen::VisitBinaryExpr(BinaryExpr *expr, AST *obj)
{
    expr->lhs->Visit(this, nullptr);
    ss << ';';
    expr->rhs->Visit(this, nullptr);
    ss << ';';
    expr->op->Visit(this, nullptr);
    return nullptr;
}

AST *CodeGen::VisitArrayExpr(ArrayExpr *expr, AST *obj)
{
    // $a,{ident},{index},$
    ss << "$a,";
    expr->identifier->Visit(this, nullptr);
    ss << ',';
    expr->index->Visit(this, nullptr);
    ss << "$^";
    return nullptr;
}

AST *CodeGen::VisitBoolExpr(BoolExpr *expr, AST *obj)
{
    
    expr->literal->Visit(this, nullptr);
    return nullptr;
}

AST *CodeGen::VisitEmptyExpr(EmptyExpr *expr, AST *obj)
{
    return nullptr;
}

AST *CodeGen::VisitErrorExpr(ErrorExpr *expr, AST *obj)
{
    return nullptr;
}

AST *CodeGen::VisitFuncCallExpr(FunctionCallExpr *expr, AST *obj)
{
    ss << "$,";
    expr->identifier->Visit(this, nullptr);
    ss << ',';
    expr->args->Visit(this, nullptr);
    ss << "$^";
    return nullptr;
}

AST *CodeGen::VisitIntExpr(IntExpr *expr, AST *obj)
{
    expr->literal->Visit(this, nullptr);
    return nullptr;
}

AST *CodeGen::VisitPostUnaryExpr(PostUnaryExpr *expr, AST *obj)
{
    expr->expr->Visit(this, nullptr);
    expr->op->Visit(this, nullptr);
    return nullptr;
}

AST *CodeGen::VisitPreUnaryExpr(PreUnaryExpr *expr, AST *obj)
{
    expr->expr->Visit(this, nullptr);
    ss << ';';
    expr->op->Visit(this, nullptr);
    return nullptr;
}

AST *CodeGen::VisitRealExpr(RealExpr *expr, AST *obj)
{
    expr->literal->Visit(this, nullptr);
    return nullptr;
}

AST *CodeGen::VisitStringExpr(StringExpr *expr, AST *obj)
{
    expr->literal->Visit(this, nullptr);
    return nullptr;
}

AST *CodeGen::VisitVarExpr(VariableExpr *expr, AST *obj)
{  
    expr->variable->Visit(this, nullptr);
    return nullptr;
}

AST *CodeGen::VisitInstructExpr(InstructExpr *expr, AST *obj)
{
    ss << "$instruct \"";
    
    // switch(expr->type)
    // {
    //     case Lexicons::Instruct::Type_Conditional:
    //     ss << "conditional ";
    //     case Lexicons::Instruct::Type_Loop:
    //     ss << "loop ";
    //     case Lexicons::Instruct::Type_Expr:
    //     case Lexicons::Instruct::Type_Assign:
    //     ss << "decl ";
    //     break;
    //     default:
    //     ss << "err ";
    //     break;
    // }

    ss << expr->value;
    ss << '\"';
    return nullptr;
}


AST *CodeGen::VisitInstructStmt(InstructStmt *stmt, AST *obj)
{
    ss << "$instruct \"";
    ss << stmt->value;
    ss << '\"';
    ss << '\n';
    
    return nullptr;
}

AST *CodeGen::VisitCallStmt(CallStmt *stmt, AST *obj)
{
    ss << "$call ";
    stmt->identifier->Visit(this, nullptr);
    ss << " ";
    stmt->args->Visit(this, nullptr);
    ss << '\n';
    return nullptr;
}

AST *CodeGen::VisitDeclStmt(DeclStmt *stmt, AST *obj)
{
    stmt->decl->Visit(this, nullptr);
    ss << '\n';
    return nullptr;
}

AST *CodeGen::VisitBreakStmt(BreakStmt *stmt, AST *obj)
{
    ss << "$break\n";
    return nullptr;
}

AST *CodeGen::VisitContinueStmt(ContinueStmt *stmt, AST *obj)
{
    ss << "$continue\n";
    return nullptr;
}

AST *CodeGen::VisitReturnStmt(ReturnStmt *stmt, AST *obj)
{
    ss << "$return ";
    stmt->expr->Visit(this, nullptr);
    ss << '\n';
    return nullptr;
}

AST *CodeGen::VisitCompoundStmt(CompoundStmt *stmt, AST *obj)
{
    ss << "$open_scope\n";
    stmt->list->Visit(this, nullptr);
    ss << "$close_scope\n";
    return nullptr;
}

AST *CodeGen::VisitWhileStmt(WhileStmt *stmt, AST *obj)
{
    ss << "$while ";
    stmt->cond->Visit(this, nullptr);
    ss << '\n';
    stmt->stmt->Visit(this, nullptr);
    ss << "$while_end\n";

    return nullptr;
}

AST *CodeGen::VisitForStmt(ForStmt *stmt, AST *obj)
{
    return nullptr;    
}

AST *CodeGen::VisitDoWhileStmt(DoWhileStmt *stmt, AST *obj)
{
    return nullptr;
}

AST *CodeGen::VisitIfStmt(IfStmt *stmt, AST *obj)
{
    ss << "$branch_begin\n";
    ss << "$if ";
    stmt->cond->Visit(this, nullptr);
    ss << '\n';
    stmt->ifStmt->Visit(this, nullptr);
    ss << "$if_end\n";
    stmt->elifList->Visit(this, nullptr);
    
    if(!stmt->elseStmt->isEmptyStmt)
    {
        ss << "$else_begin\n";
        stmt->elseStmt->Visit(this, nullptr);
        ss << "$else_end\n";
    }
    
    ss << "$branch_end\n";
    return nullptr;
}

AST *CodeGen::VisitElifStmt(ElifStmt *stmt, AST *obj)
{
    ss << "$elif ";
    stmt->cond->Visit(this, nullptr);
    ss << '\n';
    stmt->stmt->Visit(this, nullptr);
    ss << "$elif_end\n";
    return nullptr;
}

AST *CodeGen::VisitEmptyStmt(EmptyStmt *stmt, AST *obj)
{
    return nullptr;
}

AST *CodeGen::VisitErrorStmt(ErrorStmt *stmt, AST *obj)
{
    return nullptr;
}

AST *CodeGen::VisitExprStmt(ExprStmt *stmt, AST *obj)
{
    stmt->expr->Visit(this, nullptr);
    ss << '\n';
    return nullptr;
}

// Function args
AST *CodeGen::VisitArgList(ArgList *list, AST *obj)
{
    list->arg->Visit(this, nullptr);

    if(dynamic_cast<ArgList*>(list->next.get()))
    {
        ss << ',';
    }

    list->next->Visit(this, nullptr);
    return nullptr;
}

AST *CodeGen::VisitArg(Arg *arg, AST *obj)
{
    arg->expr->Visit(this, nullptr);
    return nullptr;
}

AST *CodeGen::VisitBlockItemList(BlockItemList *list, AST *obj)
{
    list->block->Visit(this, nullptr);
    list->next->Visit(this, nullptr);
    return nullptr;
}

AST *CodeGen::VisitElifList(ElifList *list, AST *obj)
{
    list->elif->Visit(this, nullptr);
    list->next->Visit(this, nullptr);
    return nullptr;
}

AST *CodeGen::VisitEmptyArgList(EmptyArgList *list, AST *obj)
{
    return nullptr;
}

AST *CodeGen::VisitEmptyBlockList(EmptyBlockList *list, AST *obj)
{
    return nullptr;
}

AST *CodeGen::VisitEmptyElifList(EmptyElifList *list, AST *obj)
{
    return nullptr;
}

AST *CodeGen::VisitEmptyVarDeclList(EmptyVarDeclList *list, AST *obj)
{
    return nullptr;
}

AST *CodeGen::VisitEmptyFuncDeclList(EmptyFuncDeclList *list, AST *obj)
{
    return nullptr;
}

AST *CodeGen::VisitEmptyParamList(EmptyParamList *list, AST *obj)
{
    return nullptr;
}

AST *CodeGen::VisitParamList(ParamList *list, AST *obj)
{
    list->param->Visit(this, nullptr);
    list->next->Visit(this, nullptr);
    return nullptr;
}

AST *CodeGen::VisitParam(Param *param, AST *obj)
{
    param->identifier->Visit(this, nullptr);
    ss << ' ';
    param->type->Visit(this, nullptr);
    ss << ' ';
    return nullptr;
}

AST *CodeGen::VisitStmtBlock(StmtBlock *block, AST *obj)
{
    block->stmt->Visit(this, nullptr);
    return nullptr;
}

AST *CodeGen::VisitVarDeclListBlock(VarDeclListBlock *block, AST *obj)
{
    return nullptr;
}

AST *CodeGen::VisitVarDeclList(VarDeclList *list, AST *obj)
{
    return nullptr;
}

// Types
// No need to do anything regarding type checking:
// exprs and stmts will do instead.
AST *CodeGen::VisitBoolType(BoolType *type, AST *obj) 
{
    ss << "$bool";
    return nullptr;
}

AST *CodeGen::VisitErrorType(ErrorType *type, AST *obj)
{
    return nullptr;
}

AST *CodeGen::VisitIntType(IntType *type, AST *obj)
{
    return nullptr;
}

AST *CodeGen::VisitArrayType(ArrayType *type, AST *obj)
{
    ss << "$array";
    return nullptr;
}

AST *CodeGen::VisitRealType(RealType *type, AST *obj)
{
    ss << "$real";
    return nullptr;
}

AST *CodeGen::VisitVoidType(VoidType *type, AST *obj)
{
    ss << "$void";
    return nullptr;
}

AST *CodeGen::VisitStringType(StringType *type, AST *obj)
{
    ss << "$string";
    return nullptr;
}

AST *CodeGen::VisitObjectType(ObjectType *type, AST *obj)
{
    ss << "$object";
    return nullptr;
}

AST *CodeGen::VisitAttributeType(AttributeType *type, AST *obj)
{
    ss << "$attribute";
    return nullptr;
}

AST *CodeGen::VisitBoolLiteral(BoolLiteral *literal, AST *obj)
{
    ss << literal->spelling;
    return nullptr;
}

AST *CodeGen::VisitIntLiteral(IntLiteral *literal, AST *obj)
{
    return nullptr;
}

AST *CodeGen::VisitRealLiteral(RealLiteral *literal, AST *obj)
{
    ss << literal->spelling;
    return nullptr;
}

AST *CodeGen::VisitStringLiteral(StringLiteral *literal, AST *obj)
{
    ss << '\"' << literal->spelling << '\"';
    return nullptr;
}

AST *CodeGen::VisitOperator(Operator *op, AST *obj)
{
    ss << op->spelling;
    return nullptr;
}

AST *CodeGen::VisitVariable(Variable *variable, AST *obj)
{
    variable->identifier->Visit(this, nullptr);
    return nullptr;
}

AST *CodeGen::VisitIdentifier(Identifier *ident, AST *obj)
{
    ss << "%" << ident->spelling << "%";
    return nullptr;
}

AST *CodeGen::VisitProgram(Program *program, AST *obj)
{
    program->list->Visit(this, nullptr);
    return nullptr;
}






