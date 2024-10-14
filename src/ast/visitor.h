#ifndef AST_VISITOR_H
#define AST_VISITOR_H

#include "../AST.h"

namespace ASTs
{
    class Visitor
    {
        public:
        // Decl
        virtual void VisitFuncDecl(FuncDecl *decl) = 0;
        virtual void VisitVarDecl(VarDecl *decl) = 0;

        // Expr
        virtual void VisitAssignExpr(AssignExpr *expr) = 0;
        virtual void VisitBinaryExpr(BinaryExpr *expr) = 0;
        virtual void VisitBoolExpr(BoolExpr *expr) = 0;
        virtual void VisitEmptyExpr(EmptyExpr *expr) = 0;
        virtual void VisitErrorExpr(ErrorExpr *expr) = 0;
        virtual void VisitFuncCallExpr(FunctionCallExpr *expr) = 0;
        virtual void VisitIntExpr(IntExpr *expr) = 0;
        virtual void VisitPostUnaryExpr(PostUnaryExpr *expr) = 0;
        virtual void VisitPreUnaryExpr(PreUnaryExpr *expr) = 0;
        virtual void VisitRealExpr(RealExpr *expr) = 0;
        virtual void VisitStringExpr(StringExpr *expr) = 0;
        virtual void VisitVarDeclExpr(VarDeclExpr *expr) = 0;
        virtual void VisitVarExpr(VariableExpr *expr) = 0;

        // Stmt
        virtual void VisitBreakStmt(BreakStmt *stmt) = 0;
        virtual void VisitCompoundStmt(CompoundStmt *stmt) = 0;
        virtual void VisitContinueStmt(ContinueStmt *stmt) = 0;
        virtual void VisitElifStmt(ElifStmt *stmt) = 0;
        virtual void VisitEmptyStmt(EmptyStmt *stmt) = 0;
        virtual void VisitErrorStmt(ErrorStmt *stmt) = 0;
        virtual void VisitExprStmt(ExprStmt *stmt) = 0;
        virtual void VisitIfStmt(IfStmt *stmt) = 0;
        virtual void VisitDoWhileStmt(DoWhileStmt *stmt) = 0;
        virtual void VisitForStmt(ForStmt *stmt) = 0;
        virtual void VisitWhileStmt(WhileStmt* Stmt) = 0;
        virtual void VisitReturnStmt(ReturnStmt *stmt) = 0;

        // Lists
        virtual void VisitArgList(ArgList *list) = 0;
        virtual void VisitArg(Arg *arg) = 0;
        virtual void VisitBlockItemList(BlockItemList *list) = 0;
        virtual void VisitElifList(ElifList *list) = 0;
        virtual void VisitEmptyArgList(EmptyArgList *list) = 0;
        virtual void VisitEmptyBlockList(EmptyBlockList *list) = 0;
        virtual void VisitEmptyElifList(EmptyElifList *list) = 0;
        virtual void VisitEmptyFuncDeclList(EmptyFuncDeclList *list) = 0;
        virtual void VisitEmptyParamList(EmptyParamList *list) = 0;
        virtual void VisitEmptyVarDeclList(EmptyVarDeclList *list) = 0;
        virtual void VisitFuncDeclList(FuncDeclList *list) = 0;
        virtual void VisitParamList(ParamList *list) = 0;
        virtual void VisitParam(Param *param) = 0;
        virtual void VisitStmtBlock(StmtBlock *block) = 0;
        virtual void VisitVarDeclBlock(VarDeclBlock *block) = 0;
        virtual void VisitVarDeclList(VarDeclList *list) = 0;

        // Types
        virtual void VisitBoolType(BoolType *type) = 0;
        virtual void VisitErrorType(ErrorType *type) = 0;
        virtual void VisitIntType(IntType *type) = 0;
        virtual void VisitRealType(RealType *type) = 0;
        virtual void VisitVoidType(VoidType *type) = 0;
        virtual void VisitStringType(StringType *type) = 0;

        // Literals
        virtual void VisitBoolLiteral(BoolLiteral *literal) = 0;
        virtual void VisitIntLiteral(IntLiteral *literal) = 0;
        virtual void VisitRealLiteral(RealLiteral *literal) = 0;
        virtual void VisitStringLiteral(StringLiteral *literal) = 0;

        // Operators
        virtual void VisitOperator(Operator *op) = 0;

        // Variables
        virtual void VisitVariable(Variable *type) = 0;
        
        // Ident
        virtual void VisitIdentifier(Identifier *ident) = 0;

    };
}
#endif