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
        void VisitFuncDecl(ASTs::FuncDecl *decl) override;
        void VisitVarDecl(ASTs::VarDecl *decl) override;

        // Expr
        void VisitAssignExpr(ASTs::AssignExpr *expr) override;
        void VisitBinaryExpr(ASTs::BinaryExpr *expr) override;
        void VisitBoolExpr(ASTs::BoolExpr *expr) override;
        void VisitEmptyExpr(ASTs::EmptyExpr *expr) override;
        void VisitErrorExpr(ASTs::ErrorExpr *expr) override;
        void VisitFuncCallExpr(ASTs::FunctionCallExpr *expr) override;
        void VisitIntExpr(ASTs::IntExpr *expr) override;
        void VisitPostUnaryExpr(ASTs::PostUnaryExpr *expr) override;
        void VisitPreUnaryExpr(ASTs::PreUnaryExpr *expr) override;
        void VisitRealExpr(ASTs::RealExpr *expr) override;
        void VisitStringExpr(ASTs::StringExpr *expr) override;
        void VisitVarDeclExpr(ASTs::VarDeclExpr *expr) override;
        void VisitVarExpr(ASTs::VariableExpr *expr) override;

        // Stmt
        void VisitBreakStmt(ASTs::BreakStmt *stmt) override;
        void VisitCompoundStmt(ASTs::CompoundStmt *stmt) override;
        void VisitContinueStmt(ASTs::ContinueStmt *stmt) override;
        void VisitElifStmt(ASTs::ElifStmt *stmt) override;
        void VisitEmptyStmt(ASTs::EmptyStmt *stmt) override;
        void VisitErrorStmt(ASTs::ErrorStmt *stmt) override;
        void VisitExprStmt(ASTs::ExprStmt *stmt) override;
        void VisitIfStmt(ASTs::IfStmt *stmt) override;
        void VisitDoWhileStmt(ASTs::DoWhileStmt *stmt) override;
        void VisitForStmt(ASTs::ForStmt *stmt) override;
        void VisitWhileStmt(ASTs::WhileStmt* Stmt) override;
        void VisitReturnStmt(ASTs::ReturnStmt *stmt) override;

        // Lists
        void VisitArgList(ASTs::ArgList *list) override;
        void VisitArg(ASTs::Arg *arg) override;
        void VisitBlockItemList(ASTs::BlockItemList *list) override;
        void VisitElifList(ASTs::ElifList *list) override;
        void VisitEmptyArgList(ASTs::EmptyArgList *list) override;
        void VisitEmptyBlockList(ASTs::EmptyBlockList *list) override;
        void VisitEmptyElifList(ASTs::EmptyElifList *list) override;
        void VisitEmptyFuncDeclList(ASTs::EmptyFuncDeclList *list) override;
        void VisitEmptyParamList(ASTs::EmptyParamList *list) override;
        void VisitEmptyVarDeclList(ASTs::EmptyVarDeclList *list) override;
        void VisitFuncDeclList(ASTs::FuncDeclList *list) override;
        void VisitParamList(ASTs::ParamList *list) override;
        void VisitParam(ASTs::Param *param) override;
        void VisitStmtBlock(ASTs::StmtBlock *block) override;
        void VisitVarDeclBlock(ASTs::VarDeclBlock *block) override;
        void VisitVarDeclList(ASTs::VarDeclList *list) override;

        // Types
        void VisitBoolType(ASTs::BoolType *type) override;
        void VisitErrorType(ASTs::ErrorType *type) override;
        void VisitIntType(ASTs::IntType *type) override;
        void VisitRealType(ASTs::RealType *type) override;
        void VisitVoidType(ASTs::VoidType *type) override;
        void VisitStringType(ASTs::StringType *type) override;

        // Literals
        void VisitBoolLiteral(ASTs::BoolLiteral *literal) override;
        void VisitIntLiteral(ASTs::IntLiteral *literal) override;
        void VisitRealLiteral(ASTs::RealLiteral *literal) override;
        void VisitStringLiteral(ASTs::StringLiteral *literal) override;

        // Operators
        void VisitOperator(ASTs::Operator *op) override;

        // Variables
        void VisitVariable(ASTs::Variable *type) override;
        
        // Ident
        void VisitIdentifier(ASTs::Identifier *ident) override;

        void VisitProgram(ASTs::Program *program) override;

    private:
    ASTs::Program *program;
    SymbolTable symbolTable;
};


#endif