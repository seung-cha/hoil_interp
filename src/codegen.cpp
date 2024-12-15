#include "codegen.h"

using namespace ASTs;

CodeGen::CodeGen(Program *program, std::vector<std::unique_ptr<ASTs::FuncDecl>>& reserve) : program{program}, reserve{reserve}
{

}


// Decls
AST *CodeGen::VisitFuncDecl(FuncDecl *decl, AST *obj)
{
    return nullptr;
}

AST *CodeGen::VisitFuncDeclList(FuncDeclList *list, AST *obj)
{
    return nullptr;
}

AST *CodeGen::VisitVarDecl(VarDecl *decl, AST *obj)
{
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
    return nullptr;
}

AST *CodeGen::VisitBoolExpr(BoolExpr *expr, AST *obj)
{
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
    return nullptr;
}

AST *CodeGen::VisitIntExpr(IntExpr *expr, AST *obj)
{
    return nullptr;
}

AST *CodeGen::VisitPostUnaryExpr(PostUnaryExpr *expr, AST *obj)
{
    return nullptr;
}

AST *CodeGen::VisitPreUnaryExpr(PreUnaryExpr *expr, AST *obj)
{
    return nullptr;
}

AST *CodeGen::VisitRealExpr(RealExpr *expr, AST *obj)
{
    return nullptr;
}

AST *CodeGen::VisitStringExpr(StringExpr *expr, AST *obj)
{
    return nullptr;
}

AST *CodeGen::VisitVarExpr(VariableExpr *expr, AST *obj)
{
    return nullptr;
}

AST *CodeGen::VisitInstructStmt(InstructStmt *stmt, AST *obj)
{
    return nullptr;
}

AST *CodeGen::VisitBreakStmt(BreakStmt *stmt, AST *obj)
{
    return nullptr;
}

AST *CodeGen::VisitContinueStmt(ContinueStmt *stmt, AST *obj)
{
    return nullptr;
}

AST *CodeGen::VisitReturnStmt(ReturnStmt *stmt, AST *obj)
{
    return nullptr;
}

AST *CodeGen::VisitCompoundStmt(CompoundStmt *stmt, AST *obj)
{
    return nullptr;
}

AST *CodeGen::VisitWhileStmt(WhileStmt *stmt, AST *obj)
{
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
    return nullptr;
}

AST *CodeGen::VisitElifStmt(ElifStmt *stmt, AST *obj)
{
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
    return nullptr;
}

// Function args
AST *CodeGen::VisitArgList(ArgList *list, AST *obj)
{
    return nullptr;
}

AST *CodeGen::VisitArg(Arg *arg, AST *obj)
{
    return nullptr;
}

AST *CodeGen::VisitBlockItemList(BlockItemList *list, AST *obj)
{
    return nullptr;
}

AST *CodeGen::VisitElifList(ElifList *list, AST *obj)
{
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
    return nullptr;
}

AST *CodeGen::VisitParam(Param *param, AST *obj)
{
    return nullptr;
}

AST *CodeGen::VisitStmtBlock(StmtBlock *block, AST *obj)
{
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

AST *CodeGen::VisitRealType(RealType *type, AST *obj)
{
    return nullptr;
}

AST *CodeGen::VisitVoidType(VoidType *type, AST *obj)
{
    return nullptr;
}

AST *CodeGen::VisitStringType(StringType *type, AST *obj)
{
    return nullptr;
}

AST *CodeGen::VisitBoolLiteral(BoolLiteral *literal, AST *obj)
{
    return nullptr;
}

AST *CodeGen::VisitIntLiteral(IntLiteral *literal, AST *obj)
{
    return nullptr;
}

AST *CodeGen::VisitRealLiteral(RealLiteral *literal, AST *obj)
{
    return nullptr;
}

AST *CodeGen::VisitStringLiteral(StringLiteral *literal, AST *obj)
{
    return nullptr;
}

AST *CodeGen::VisitOperator(Operator *op, AST *obj)
{
    return nullptr;
}

AST *CodeGen::VisitVariable(Variable *variable, AST *obj)
{
    return nullptr;
}

AST *CodeGen::VisitIdentifier(Identifier *ident, AST *obj)
{
    return nullptr;
}

AST *CodeGen::VisitProgram(Program *program, AST *obj)
{
    return nullptr;
}






