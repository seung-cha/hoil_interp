#ifndef CODEGEN_H
#define CODEGEN_H

#include <vector>
#include <memory>

#include "ast/visitor.h"
#include "AST.h"


class CodeGen : public ASTs::Visitor
{
    public:
    CodeGen(ASTs::Program *program, std::vector<std::unique_ptr<ASTs::FuncDecl>>& reserve);
    // Decl
    virtual ASTs::AST *VisitFuncDecl(ASTs::FuncDecl *decl, ASTs::AST *obj) override;
    virtual ASTs::AST *VisitVarDecl(ASTs::VarDecl *decl, ASTs::AST *obj) override;

    // Expr
    virtual ASTs::AST *VisitAssignExpr(ASTs::AssignExpr *expr, ASTs::AST *obj) override;
    virtual ASTs::AST *VisitBinaryExpr(ASTs::BinaryExpr *expr, ASTs::AST *obj) override;
    virtual ASTs::AST *VisitBoolExpr(ASTs::BoolExpr *expr, ASTs::AST *obj) override;
    virtual ASTs::AST *VisitEmptyExpr(ASTs::EmptyExpr *expr, ASTs::AST *obj) override;
    virtual ASTs::AST *VisitErrorExpr(ASTs::ErrorExpr *expr, ASTs::AST *obj) override;
    virtual ASTs::AST *VisitFuncCallExpr(ASTs::FunctionCallExpr *expr, ASTs::AST *obj) override;
    virtual ASTs::AST *VisitIntExpr(ASTs::IntExpr *expr, ASTs::AST *obj) override;
    virtual ASTs::AST *VisitPostUnaryExpr(ASTs::PostUnaryExpr *expr, ASTs::AST *obj) override;
    virtual ASTs::AST *VisitPreUnaryExpr(ASTs::PreUnaryExpr *expr, ASTs::AST *obj) override;
    virtual ASTs::AST *VisitRealExpr(ASTs::RealExpr *expr, ASTs::AST *obj) override;
    virtual ASTs::AST *VisitStringExpr(ASTs::StringExpr *expr, ASTs::AST *obj) override;
    virtual ASTs::AST *VisitVarDeclExpr(ASTs::VarDeclExpr *expr, ASTs::AST *obj) override;
    virtual ASTs::AST *VisitVarExpr(ASTs::VariableExpr *expr, ASTs::AST *obj) override;

    // Stmt
    virtual ASTs::AST *VisitBreakStmt(ASTs::BreakStmt *stmt, ASTs::AST *obj) override;
    virtual ASTs::AST *VisitCompoundStmt(ASTs::CompoundStmt *stmt, ASTs::AST *obj) override;
    virtual ASTs::AST *VisitContinueStmt(ASTs::ContinueStmt *stmt, ASTs::AST *obj) override;
    virtual ASTs::AST *VisitElifStmt(ASTs::ElifStmt *stmt, ASTs::AST *obj) override;
    virtual ASTs::AST *VisitEmptyStmt(ASTs::EmptyStmt *stmt, ASTs::AST *obj) override;
    virtual ASTs::AST *VisitErrorStmt(ASTs::ErrorStmt *stmt, ASTs::AST *obj) override;
    virtual ASTs::AST *VisitExprStmt(ASTs::ExprStmt *stmt, ASTs::AST *obj) override;
    virtual ASTs::AST *VisitIfStmt(ASTs::IfStmt *stmt, ASTs::AST *obj) override;
    virtual ASTs::AST *VisitDoWhileStmt(ASTs::DoWhileStmt *stmt, ASTs::AST *obj) override;
    virtual ASTs::AST *VisitForStmt(ASTs::ForStmt *stmt, ASTs::AST *obj) override;
    virtual ASTs::AST *VisitWhileStmt(ASTs::WhileStmt* Stmt, ASTs::AST *obj) override;
    virtual ASTs::AST *VisitReturnStmt(ASTs::ReturnStmt *stmt, ASTs::AST *obj) override;
    virtual ASTs::AST *VisitInstructStmt(ASTs::InstructStmt *stmt, ASTs::AST *obj) override;

    // Lists
    virtual ASTs::AST *VisitArgList(ASTs::ArgList *list, ASTs::AST *obj) override;
    virtual ASTs::AST *VisitArg(ASTs::Arg *arg, ASTs::AST *obj) override;
    virtual ASTs::AST *VisitBlockItemList(ASTs::BlockItemList *list, ASTs::AST *obj) override;
    virtual ASTs::AST *VisitElifList(ASTs::ElifList *list, ASTs::AST *obj) override;
    virtual ASTs::AST *VisitEmptyArgList(ASTs::EmptyArgList *list, ASTs::AST *obj) override;
    virtual ASTs::AST *VisitEmptyBlockList(ASTs::EmptyBlockList *list, ASTs::AST *obj) override;
    virtual ASTs::AST *VisitEmptyElifList(ASTs::EmptyElifList *list, ASTs::AST *obj) override;
    virtual ASTs::AST *VisitEmptyFuncDeclList(ASTs::EmptyFuncDeclList *list, ASTs::AST *obj) override;
    virtual ASTs::AST *VisitEmptyParamList(ASTs::EmptyParamList *list, ASTs::AST *obj) override;
    virtual ASTs::AST *VisitEmptyVarDeclList(ASTs::EmptyVarDeclList *list, ASTs::AST *obj) override;
    virtual ASTs::AST *VisitFuncDeclList(ASTs::FuncDeclList *list, ASTs::AST *obj) override;
    virtual ASTs::AST *VisitParamList(ASTs::ParamList *list, ASTs::AST *obj) override;
    virtual ASTs::AST *VisitParam(ASTs::Param *param, ASTs::AST *obj) override;
    virtual ASTs::AST *VisitStmtBlock(ASTs::StmtBlock *block, ASTs::AST *obj) override;
    virtual ASTs::AST *VisitVarDeclListBlock(ASTs::VarDeclListBlock *block, ASTs::AST *obj) override;
    virtual ASTs::AST *VisitVarDeclList(ASTs::VarDeclList *list, ASTs::AST *obj) override;

    // Types
    virtual ASTs::AST *VisitBoolType(ASTs::BoolType *type, ASTs::AST *obj) override;
    virtual ASTs::AST *VisitErrorType(ASTs::ErrorType *type, ASTs::AST *obj) override;
    virtual ASTs::AST *VisitIntType(ASTs::IntType *type, ASTs::AST *obj) override;
    virtual ASTs::AST *VisitRealType(ASTs::RealType *type, ASTs::AST *obj) override;
    virtual ASTs::AST *VisitVoidType(ASTs::VoidType *type, ASTs::AST *obj) override;
    virtual ASTs::AST *VisitStringType(ASTs::StringType *type, ASTs::AST *obj) override;

    // Literals
    virtual ASTs::AST *VisitBoolLiteral(ASTs::BoolLiteral *literal, ASTs::AST *obj) override;
    virtual ASTs::AST *VisitIntLiteral(ASTs::IntLiteral *literal, ASTs::AST *obj) override;
    virtual ASTs::AST *VisitRealLiteral(ASTs::RealLiteral *literal, ASTs::AST *obj) override;
    virtual ASTs::AST *VisitStringLiteral(ASTs::StringLiteral *literal, ASTs::AST *obj) override;

    // Operators
    virtual ASTs::AST *VisitOperator(ASTs::Operator *op, ASTs::AST *obj) override;

    // Variables
    virtual ASTs::AST *VisitVariable(ASTs::Variable *variable, ASTs::AST *obj) override;
    
    // Ident
    virtual ASTs::AST *VisitIdentifier(ASTs::Identifier *ident, ASTs::AST *obj) override;

    virtual ASTs::AST *VisitProgram(ASTs::Program *program, ASTs::AST *obj) override;

    private:
    ASTs::Program *program;
    std::vector<std::unique_ptr<ASTs::FuncDecl>>& reserve;

};

#endif