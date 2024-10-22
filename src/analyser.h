#ifndef ANALYSER_H
#define ANALYSER_H

#include "symbol_table.h"
#include "ast/visitor.h"
#include "AST.h"
#include <vector>
#include <string>

class Analyser : public ASTs::Visitor
{
    public:
    Analyser(ASTs::Program *program);
    std::vector<std::string> errorMsgs;

    // Decl
    virtual AST *VisitFuncDecl(FuncDecl *decl, AST *obj) override;
    virtual AST *VisitVarDecl(VarDecl *decl, AST *obj) override;

    // Expr
    virtual AST *VisitAssignExpr(AssignExpr *expr, AST *obj) override;
    virtual AST *VisitBinaryExpr(BinaryExpr *expr, AST *obj) override;
    virtual AST *VisitBoolExpr(BoolExpr *expr, AST *obj) override;
    virtual AST *VisitEmptyExpr(EmptyExpr *expr, AST *obj) override;
    virtual AST *VisitErrorExpr(ErrorExpr *expr, AST *obj) override;
    virtual AST *VisitFuncCallExpr(FunctionCallExpr *expr, AST *obj) override;
    virtual AST *VisitIntExpr(IntExpr *expr, AST *obj) override;
    virtual AST *VisitPostUnaryExpr(PostUnaryExpr *expr, AST *obj) override;
    virtual AST *VisitPreUnaryExpr(PreUnaryExpr *expr, AST *obj) override;
    virtual AST *VisitRealExpr(RealExpr *expr, AST *obj) override;
    virtual AST *VisitStringExpr(StringExpr *expr, AST *obj) override;
    virtual AST *VisitVarDeclExpr(VarDeclExpr *expr, AST *obj) override;
    virtual AST *VisitVarExpr(VariableExpr *expr, AST *obj) override;

    // Stmt
    virtual AST *VisitBreakStmt(BreakStmt *stmt, AST *obj) override;
    virtual AST *VisitCompoundStmt(CompoundStmt *stmt, AST *obj) override;
    virtual AST *VisitContinueStmt(ContinueStmt *stmt, AST *obj) override;
    virtual AST *VisitElifStmt(ElifStmt *stmt, AST *obj) override;
    virtual AST *VisitEmptyStmt(EmptyStmt *stmt, AST *obj) override;
    virtual AST *VisitErrorStmt(ErrorStmt *stmt, AST *obj) override;
    virtual AST *VisitExprStmt(ExprStmt *stmt, AST *obj) override;
    virtual AST *VisitIfStmt(IfStmt *stmt, AST *obj) override;
    virtual AST *VisitDoWhileStmt(DoWhileStmt *stmt, AST *obj) override;
    virtual AST *VisitForStmt(ForStmt *stmt, AST *obj) override;
    virtual AST *VisitWhileStmt(WhileStmt* Stmt, AST *obj) override;
    virtual AST *VisitReturnStmt(ReturnStmt *stmt, AST *obj) override;

    // Lists
    virtual AST *VisitArgList(ArgList *list, AST *obj) override;
    virtual AST *VisitArg(Arg *arg, AST *obj) override;
    virtual AST *VisitBlockItemList(BlockItemList *list, AST *obj) override;
    virtual AST *VisitElifList(ElifList *list, AST *obj) override;
    virtual AST *VisitEmptyArgList(EmptyArgList *list, AST *obj) override;
    virtual AST *VisitEmptyBlockList(EmptyBlockList *list, AST *obj) override;
    virtual AST *VisitEmptyElifList(EmptyElifList *list, AST *obj) override;
    virtual AST *VisitEmptyFuncDeclList(EmptyFuncDeclList *list, AST *obj) override;
    virtual AST *VisitEmptyParamList(EmptyParamList *list, AST *obj) override;
    virtual AST *VisitEmptyVarDeclList(EmptyVarDeclList *list, AST *obj) override;
    virtual AST *VisitFuncDeclList(FuncDeclList *list, AST *obj) override;
    virtual AST *VisitParamList(ParamList *list, AST *obj) override;
    virtual AST *VisitParam(Param *param, AST *obj) override;
    virtual AST *VisitStmtBlock(StmtBlock *block, AST *obj) override;
    virtual AST *VisitVarDeclListBlock(VarDeclListBlock *block, AST *obj) override;
    virtual AST *VisitVarDeclList(VarDeclList *list, AST *obj) override;

    // Types
    virtual AST *VisitBoolType(BoolType *type, AST *obj) override;
    virtual AST *VisitErrorType(ErrorType *type, AST *obj) override;
    virtual AST *VisitIntType(IntType *type, AST *obj) override;
    virtual AST *VisitRealType(RealType *type, AST *obj) override;
    virtual AST *VisitVoidType(VoidType *type, AST *obj) override;
    virtual AST *VisitStringType(StringType *type, AST *obj) override;

    // Literals
    virtual AST *VisitBoolLiteral(BoolLiteral *literal, AST *obj) override;
    virtual AST *VisitIntLiteral(IntLiteral *literal, AST *obj) override;
    virtual AST *VisitRealLiteral(RealLiteral *literal, AST *obj) override;
    virtual AST *VisitStringLiteral(StringLiteral *literal, AST *obj) override;

    // Operators
    virtual AST *VisitOperator(Operator *op, AST *obj) override;

    // Variables
    virtual AST *VisitVariable(Variable *variable, AST *obj) override;
    
    // Ident
    virtual AST *VisitIdentifier(Identifier *ident, AST *obj) override;

    virtual AST *VisitProgram(Program *program, AST *obj) override;

    private:
    ASTs::Program *program;
    SymbolTable symbolTable;

    void ReportError(std::string str)
    {
        errorMsgs.push_back(str);
    }
    
};


#endif