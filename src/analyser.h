#ifndef ANALYSER_H
#define ANALYSER_H

#include "symbol_table.h"
#include "ast/visitor.h"
#include "AST.h"

class Analyser : public ASTs::Visitor
{
    public:
    Analyser(ASTs::Program *program);

    // Decl
        virtual void VisitFuncDecl(ASTs::FuncDecl *decl) override;
        virtual void VisitVarDecl(ASTs::VarDecl *decl) override;

        // Expr
        virtual void VisitAssignExpr(ASTs::AssignExpr *expr) override;
        virtual void VisitBinaryExpr(ASTs::BinaryExpr *expr) override;
        virtual void VisitBoolExpr(ASTs::BoolExpr *expr) override;
        virtual void VisitEmptyExpr(ASTs::EmptyExpr *expr) override;
        virtual void VisitErrorExpr(ASTs::ErrorExpr *expr) override;
        virtual void VisitFuncCallExpr(ASTs::FunctionCallExpr *expr) override;
        virtual void VisitIntExpr(ASTs::IntExpr *expr) override;
        virtual void VisitPostUnaryExpr(ASTs::PostUnaryExpr *expr) override;
        virtual void VisitPreUnaryExpr(ASTs::PreUnaryExpr *expr) override;
        virtual void VisitRealExpr(ASTs::RealExpr *expr) override;
        virtual void VisitStringExpr(ASTs::StringExpr *expr) override;
        virtual void VisitVarDeclExpr(ASTs::VarDeclExpr *expr) override;
        virtual void VisitVarExpr(ASTs::VariableExpr *expr) override;

        // Stmt
        virtual void VisitBreakStmt(ASTs::BreakStmt *stmt) override;
        virtual void VisitCompoundStmt(ASTs::CompoundStmt *stmt) override;
        virtual void VisitContinueStmt(ASTs::ContinueStmt *stmt) override;
        virtual void VisitElifStmt(ASTs::ElifStmt *stmt) override;
        virtual void VisitEmptyStmt(ASTs::EmptyStmt *stmt) override;
        virtual void VisitErrorStmt(ASTs::ErrorStmt *stmt) override;
        virtual void VisitExprStmt(ASTs::ExprStmt *stmt) override;
        virtual void VisitIfStmt(ASTs::IfStmt *stmt) override;
        virtual void VisitDoWhileStmt(ASTs::DoWhileStmt *stmt) override;
        virtual void VisitForStmt(ASTs::ForStmt *stmt) override;
        virtual void VisitWhileStmt(ASTs::WhileStmt* Stmt) override;
        virtual void VisitReturnStmt(ASTs::ReturnStmt *stmt) override;

        // Lists
        virtual void VisitArgList(ASTs::ArgList *list) override;
        virtual void VisitArg(ASTs::Arg *arg) override;
        virtual void VisitBlockItemList(ASTs::BlockItemList *list) override;
        virtual void VisitElifList(ASTs::ElifList *list) override;
        virtual void VisitEmptyArgList(ASTs::EmptyArgList *list) override;
        virtual void VisitEmptyBlockList(ASTs::EmptyBlockList *list) override;
        virtual void VisitEmptyElifList(ASTs::EmptyElifList *list) override;
        virtual void VisitEmptyFuncDeclList(ASTs::EmptyFuncDeclList *list) override;
        virtual void VisitEmptyParamList(ASTs::EmptyParamList *list) override;
        virtual void VisitEmptyVarDeclList(ASTs::EmptyVarDeclList *list) override;
        virtual void VisitFuncDeclList(ASTs::FuncDeclList *list) override;
        virtual void VisitParamList(ASTs::ParamList *list) override;
        virtual void VisitParam(ASTs::Param *param) override;
        virtual void VisitStmtBlock(ASTs::StmtBlock *block) override;
        virtual void VisitVarDeclBlock(ASTs::VarDeclBlock *block) override;
        virtual void VisitVarDeclList(ASTs::VarDeclList *list) override;

        // Types
        virtual void VisitBoolType(ASTs::BoolType *type) override;
        virtual void VisitErrorType(ASTs::ErrorType *type) override;
        virtual void VisitIntType(ASTs::IntType *type) override;
        virtual void VisitRealType(ASTs::RealType *type) override;
        virtual void VisitVoidType(ASTs::VoidType *type) override;
        virtual void VisitStringType(ASTs::StringType *type) override;

        // Literals
        virtual void VisitBoolLiteral(ASTs::BoolLiteral *literal) override;
        virtual void VisitIntLiteral(ASTs::IntLiteral *literal) override;
        virtual void VisitRealLiteral(ASTs::RealLiteral *literal) override;
        virtual void VisitStringLiteral(ASTs::StringLiteral *literal) override;

        // Operators
        virtual void VisitOperator(ASTs::Operator *op) override;

        // Variables
        virtual void VisitVariable(ASTs::Variable *type) override;
        
        // Ident
        virtual void VisitIdentifier(ASTs::Identifier *ident) override;

        virtual void VisitProgram(ASTs::Program *program) override;

    private:
    ASTs::Program *program;
    SymbolTable symbolTable;
};


#endif