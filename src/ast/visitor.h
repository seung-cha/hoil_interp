#ifndef AST_VISITOR_H
#define AST_VISITOR_H

namespace ASTs
{
    class AST;
    class FuncDecl;
    class VarDecl;
    class AssignExpr;
    class BinaryExpr;
    class BoolExpr;
    class EmptyExpr;
    class ErrorExpr;
    class FunctionCallExpr;
    class IntExpr;
    class PostUnaryExpr;
    class PreUnaryExpr;
    class RealExpr;
    class StringExpr;
    class VarDeclExpr;
    class VariableExpr;

    class BreakStmt;
    class CompoundStmt;
    class ContinueStmt;
    class ElifStmt;
    class EmptyStmt;
    class ErrorStmt;
    class ExprStmt;
    class IfStmt;
    class DoWhileStmt;
    class ForStmt;
    class WhileStmt;
    class ReturnStmt;
    class InstructStmt;
    class DeclStmt;

    
    class ArgList;
    class Arg;
    class BlockItemList;
    class ElifList;
    class EmptyArgList;
    class EmptyBlockList;
    class EmptyElifList;
    class EmptyFuncDeclList;
    class EmptyParamList;
    class EmptyVarDeclList;
    class FuncDeclList;
    class ParamList;
    class Param;
    class StmtBlock;
    class VarDeclListBlock;
    class VarDeclList;

    class BoolType;
    class ErrorType;
    class IntType;
    class RealType;
    class VoidType;
    class StringType; 
    class ObjectType;
    class AttributeType;

    class BoolLiteral;
    class IntLiteral;
    class RealLiteral;
    class StringLiteral;

    class Operator;
    class Variable;
    class Identifier;

    
    class Program;

    class Visitor
    {
        public:
        // Decl
        virtual AST *VisitFuncDecl(FuncDecl *decl, AST *obj) = 0;
        virtual AST *VisitVarDecl(VarDecl *decl, AST *obj) = 0;

        // Expr
        virtual AST *VisitAssignExpr(AssignExpr *expr, AST *obj) = 0;
        virtual AST *VisitBinaryExpr(BinaryExpr *expr, AST *obj) = 0;
        virtual AST *VisitBoolExpr(BoolExpr *expr, AST *obj) = 0;
        virtual AST *VisitEmptyExpr(EmptyExpr *expr, AST *obj) = 0;
        virtual AST *VisitErrorExpr(ErrorExpr *expr, AST *obj) = 0;
        virtual AST *VisitFuncCallExpr(FunctionCallExpr *expr, AST *obj) = 0;
        virtual AST *VisitIntExpr(IntExpr *expr, AST *obj) = 0;
        virtual AST *VisitPostUnaryExpr(PostUnaryExpr *expr, AST *obj) = 0;
        virtual AST *VisitPreUnaryExpr(PreUnaryExpr *expr, AST *obj) = 0;
        virtual AST *VisitRealExpr(RealExpr *expr, AST *obj) = 0;
        virtual AST *VisitStringExpr(StringExpr *expr, AST *obj) = 0;
        virtual AST *VisitVarDeclExpr(VarDeclExpr *expr, AST *obj) = 0;
        virtual AST *VisitVarExpr(VariableExpr *expr, AST *obj) = 0;

        // Stmt
        virtual AST *VisitBreakStmt(BreakStmt *stmt, AST *obj) = 0;
        virtual AST *VisitCompoundStmt(CompoundStmt *stmt, AST *obj) = 0;
        virtual AST *VisitContinueStmt(ContinueStmt *stmt, AST *obj) = 0;
        virtual AST *VisitElifStmt(ElifStmt *stmt, AST *obj) = 0;
        virtual AST *VisitEmptyStmt(EmptyStmt *stmt, AST *obj) = 0;
        virtual AST *VisitErrorStmt(ErrorStmt *stmt, AST *obj) = 0;
        virtual AST *VisitExprStmt(ExprStmt *stmt, AST *obj) = 0;
        virtual AST *VisitIfStmt(IfStmt *stmt, AST *obj) = 0;
        virtual AST *VisitDoWhileStmt(DoWhileStmt *stmt, AST *obj) = 0;
        virtual AST *VisitForStmt(ForStmt *stmt, AST *obj) = 0;
        virtual AST *VisitWhileStmt(WhileStmt* Stmt, AST *obj) = 0;
        virtual AST *VisitReturnStmt(ReturnStmt *stmt, AST *obj) = 0;
        virtual AST *VisitInstructStmt(InstructStmt *stmt, AST *obj) = 0;
        virtual AST *VisitDeclStmt(DeclStmt *stmt, AST *obj) = 0;

        // Lists
        virtual AST *VisitArgList(ArgList *list, AST *obj) = 0;
        virtual AST *VisitArg(Arg *arg, AST *obj) = 0;
        virtual AST *VisitBlockItemList(BlockItemList *list, AST *obj) = 0;
        virtual AST *VisitElifList(ElifList *list, AST *obj) = 0;
        virtual AST *VisitEmptyArgList(EmptyArgList *list, AST *obj) = 0;
        virtual AST *VisitEmptyBlockList(EmptyBlockList *list, AST *obj) = 0;
        virtual AST *VisitEmptyElifList(EmptyElifList *list, AST *obj) = 0;
        virtual AST *VisitEmptyFuncDeclList(EmptyFuncDeclList *list, AST *obj) = 0;
        virtual AST *VisitEmptyParamList(EmptyParamList *list, AST *obj) = 0;
        virtual AST *VisitEmptyVarDeclList(EmptyVarDeclList *list, AST *obj) = 0;
        virtual AST *VisitFuncDeclList(FuncDeclList *list, AST *obj) = 0;
        virtual AST *VisitParamList(ParamList *list, AST *obj) = 0;
        virtual AST *VisitParam(Param *param, AST *obj) = 0;
        virtual AST *VisitStmtBlock(StmtBlock *block, AST *obj) = 0;
        virtual AST *VisitVarDeclListBlock(VarDeclListBlock *block, AST *obj) = 0;
        virtual AST *VisitVarDeclList(VarDeclList *list, AST *obj) = 0;

        // Types
        virtual AST *VisitBoolType(BoolType *type, AST *obj) = 0;
        virtual AST *VisitErrorType(ErrorType *type, AST *obj) = 0;
        virtual AST *VisitIntType(IntType *type, AST *obj) = 0;
        virtual AST *VisitRealType(RealType *type, AST *obj) = 0;
        virtual AST *VisitVoidType(VoidType *type, AST *obj) = 0;
        virtual AST *VisitStringType(StringType *type, AST *obj) = 0;
        virtual AST *VisitObjectType(ObjectType *type, AST *obj) = 0;
        virtual AST *VisitAttributeType(AttributeType *type, AST *obj) = 0;

        // Literals
        virtual AST *VisitBoolLiteral(BoolLiteral *literal, AST *obj) = 0;
        virtual AST *VisitIntLiteral(IntLiteral *literal, AST *obj) = 0;
        virtual AST *VisitRealLiteral(RealLiteral *literal, AST *obj) = 0;
        virtual AST *VisitStringLiteral(StringLiteral *literal, AST *obj) = 0;

        // Operators
        virtual AST *VisitOperator(Operator *op, AST *obj) = 0;

        // Variables
        virtual AST *VisitVariable(Variable *variable, AST *obj) = 0;
        
        // Ident
        virtual AST *VisitIdentifier(Identifier *ident, AST *obj) = 0;

        virtual AST *VisitProgram(Program *program, AST *obj) = 0;

    };
}
#endif