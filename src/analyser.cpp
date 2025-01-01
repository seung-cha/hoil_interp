#include "analyser.h"
#include <memory>
#include <sstream>
#include <cassert>

using namespace ASTs;

Analyser::Analyser(Program *program, std::vector<std::unique_ptr<ASTs::FuncDecl>>& reserve) : program{program}
{
    symbolTable.OpenScope();

    // Copy over reserved functions
    for(auto& decl : reserve)
    {
        symbolTable.Insert(decl->identifier->spelling, decl.get());
    }

    program->Visit(this, nullptr);
    symbolTable.CloseScope();

    if(symbolTable.level != -1)
    {
        std::cout << "Symbol Table level is not -1 after termination?" << std::endl;
        std::cout << "Level: " << symbolTable.level << std::endl;
    }
}

// Decls
AST *Analyser::VisitFuncDecl(FuncDecl *decl, AST *obj)
{
    decl->isFuncDecl = true;

    if(!symbolTable.Insert(decl->identifier->spelling, decl))
    {
        std::stringstream ss;
        ss << "Function is already declared: " << decl->identifier->spelling;
        ReportError(ss.str());
    }

    decl->stmt->Visit(this, decl);
    return nullptr;
}

AST *Analyser::VisitFuncDeclList(FuncDeclList *list, AST *obj)
{
    list->decl->Visit(this, nullptr);
    list->next->Visit(this, nullptr);
    return nullptr;
}

AST *Analyser::VisitVarDecl(VarDecl *decl, AST *obj)
{
    // Void type represents none value
    decl->isVarDecl = true;
    if(Decl *prev_decl = symbolTable.Lookup(decl->identifier->spelling))
    {
        // Already declared
        
        // Check if variable is declared explicitly again
        if(!decl->type->IsVoidType())
        {
            if(!decl->type->Compatible(prev_decl->type.get()))
            {
                ReportError("Identifier is re-declared with a different type. This is not allowed.");
                decl->type = std::move(std::make_unique<ErrorType>(decl->lineNo, decl->charNo));
            }
        }
        else
        {
            decl->type = prev_decl->type->DeepCopy();
        }

        decl->expr->Visit(this, nullptr);

        if(decl->expr->isEmptyExpr)
        {
            ReportError("Variable is re-declared without a value. This is not allowed.");
            decl->type = std::move(std::make_unique<ErrorType>(decl->lineNo, decl->charNo));
        }
        else if(!decl->expr->type->Compatible(decl->type.get()))
        {
            //TODO: Sophisticated error type
            ReportError("Incompatible variable assignment!");
            decl->type = std::move(std::make_unique<ErrorType>(decl->lineNo, decl->charNo));

        }
    }
    else
    {
        symbolTable.Insert(decl->identifier->spelling, decl);
        // Var is newly declared.
        decl->expr->Visit(this, nullptr);
        if(decl->type->IsVoidType())
        {
            decl->type = decl->expr->type->DeepCopy();
        }
        else if(!decl->expr->isEmptyExpr && !decl->expr->type->Compatible(decl->type.get()))
        {
            
            //TODO: Sophisticated error type
            ReportError("Incompatible variable assignment!");
            decl->type = std::move(std::make_unique<ErrorType>(decl->lineNo, decl->charNo));
        }
    }

    return nullptr;
}

AST *Analyser::VisitVarDeclExpr(VarDeclExpr *expr, AST *obj)
{
    // Visit underlying expr, return type
    expr->expr->Visit(this, nullptr);

    if(expr->expr->type)
    {
        expr->type = expr->expr->type->DeepCopy();
    }

    return expr->type.get();
}

// Exprs
AST *Analyser::VisitAssignExpr(AssignExpr *expr, AST *obj)
{
    expr->lhs->Visit(this, nullptr);
    expr->rhs->Visit(this, nullptr);

    if(!expr->op->Compatible(expr->lhs->type.get(), expr->rhs->type.get()))
    {
        ReportError("Assignment Expression Type is Incompatible!");
        expr->type = std::make_unique<ErrorType>(expr->lineNo, expr->charNo);
    }
    else if(!expr->lhs->assignable)
    {
        ReportError("Left-hand-side of the expression is unassignable!");
        expr->type = std::make_unique<ErrorType>(expr->lineNo, expr->charNo);
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
        ReportError("Binary Expression Type is Incompatible!");
        expr->type = std::make_unique<ErrorType>(expr->lineNo, expr->charNo);
    }
    else
    {
        if(expr->op->IsBoolOp())
        {
            if(expr->lhs->type->IsAttributeType() || expr->lhs->type->IsStringType())
            {
                expr->type = std::make_unique<ObjectType>(expr->lineNo, expr->charNo);
            }
            else
            {
                expr->type = std::make_unique<BoolType>(expr->lineNo, expr->charNo);
            }
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
    expr->type = std::make_unique<BoolType>(expr->lineNo, expr->charNo);
    return expr->type.get();
}

AST *Analyser::VisitEmptyExpr(EmptyExpr *expr, AST *obj)
{
    expr->isEmptyExpr = true;
    return nullptr;
}

AST *Analyser::VisitErrorExpr(ErrorExpr *expr, AST *obj)
{
    return nullptr;
}

AST *Analyser::VisitFuncCallExpr(FunctionCallExpr *expr, AST *obj)
{
    Decl *decl = symbolTable.Lookup(expr->identifier->spelling);

    if(!decl || !decl->isFuncDecl)
    {
        std::ostringstream ss;
        ss << "Unknown Function Identifier: " << expr->identifier->spelling;
        ReportError(ss.str());
        expr->type = std::move(std::make_unique<ErrorType>(expr->type->lineNo, expr->type->charNo));
    }
    else
    {
        expr->type = decl->type->DeepCopy();
        expr->args->Visit(this, dynamic_cast<FuncDecl*>(decl)->params.get());
    }

    return nullptr;
}

AST *Analyser::VisitIntExpr(IntExpr *expr, AST *obj)
{
    expr->type = std::make_unique<IntType>(expr->lineNo, expr->charNo);
    return expr->type.get();
}

AST *Analyser::VisitPostUnaryExpr(PostUnaryExpr *expr, AST *obj)
{
    expr->expr->Visit(this, nullptr);

    // TODO: Make sure expr is a variable
    if(!expr->op->Compatible(expr->expr->type.get(), nullptr))
    {
        char c[1024];
        snprintf(c, sizeof(c), "Unary expression type is incompatible! %d:%d", expr->lineNo, expr->charNo);
        ReportError(c);
        expr->type = std::make_unique<ErrorType>(expr->lineNo, expr->charNo);
    }
    else
    {
        if(expr->op->IsBoolOp())
        {
            expr->type = std::make_unique<BoolType>(expr->lineNo, expr->charNo);
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
    expr->expr->Visit(this, nullptr);


    // TODO: Make sure expr is a variable
    if(!expr->op->Compatible(expr->expr->type.get(), nullptr))
    {
        ReportError("Unary Expression Type is incompatible!");
        expr->type = std::make_unique<ErrorType>(expr->lineNo, expr->charNo);
    }
    else
    {
        if(expr->op->IsBoolOp())
        {
            expr->type = std::make_unique<BoolType>(expr->lineNo, expr->charNo);
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
    expr->type = std::make_unique<RealType>(expr->lineNo, expr->charNo);
    return expr->type.get();
}

AST *Analyser::VisitStringExpr(StringExpr *expr, AST *obj)
{
    expr->type = std::make_unique<StringType>(expr->lineNo, expr->charNo);
    return expr->type.get();
}

AST *Analyser::VisitVarExpr(VariableExpr *expr, AST *obj)
{
    Decl *decl = symbolTable.Lookup(expr->variable->identifier->spelling);
    expr->assignable = true;
    
    if(!decl || !(decl->isVarDecl || decl->isParamDecl))
    {
        std::ostringstream ss;
        ss << "Identifier not found: " << expr->variable->identifier->spelling;
        ReportError(ss.str());
        expr->type = std::move(std::make_unique<ErrorType>(expr->lineNo, expr->charNo));
    }
    else
    {
        expr->type = decl->type->DeepCopy();
    }

    return expr->type.get();
}

AST *Analyser::VisitBreakStmt(BreakStmt *stmt, AST *obj)
{

    if(!symbolTable.peek().isLoopScope)
    {
        ReportError("break is called inside a non-loop scope.");
    }

    return nullptr;
}

AST *Analyser::VisitContinueStmt(ContinueStmt *stmt, AST *obj)
{
    if(!symbolTable.peek().isLoopScope)
    {
        ReportError("continue is called inside a non-loop scope.");
    }

    return nullptr;
}

AST *Analyser::VisitReturnStmt(ReturnStmt *stmt, AST *obj)
{

    if(!symbolTable.peek().isFunctionScope)
    {
        ReportError("return is called inside a non-function scope.");
    }

    Decl *funcDecl = nullptr;
    assert((funcDecl = dynamic_cast<FuncDecl*>(obj)) && "VisitReturnStmt received obj that is not a func decl?");

    stmt->expr->Visit(this, obj);

    if(funcDecl->type->IsVoidType() && !stmt->expr->isEmptyExpr)
    {
        std::stringstream ss;
        ss << "Function is declared to not return a value but is returning something: " << funcDecl->identifier->spelling;
        ReportError(ss.str());
    }
    else if(!funcDecl->type->IsVoidType() && stmt->expr->isEmptyExpr)
    {
        std::stringstream ss;
        ss << "Function is declared to return a value but is returning nothing: " << funcDecl->identifier->spelling;
        ReportError(ss.str());
    }
    else if(!stmt->expr->isEmptyExpr && !funcDecl->type->Compatible(stmt->expr->type.get()))
    { 
        std::stringstream ss;
        ss << "Return type mismatch!: " << funcDecl->identifier->spelling;
        ReportError(ss.str());
    }
    

    return nullptr;
}

AST *Analyser::VisitCompoundStmt(CompoundStmt *stmt, AST *obj)
{
    // Accept args decl and initialise it here?
    //assert(obj && "Nothing has been passed to VisitCompoundStmt()");
    symbolTable.OpenScope();

    if(FuncDecl *decl = dynamic_cast<FuncDecl*>(obj))
    {
        symbolTable.peek().isFunctionScope = true;
        decl->params->Visit(this, nullptr);
    }
    else if(Stmt *parentStmt = dynamic_cast<Stmt*>(obj))
    {
        stmt->isLoopBody = parentStmt->isLoopStmt;
        symbolTable.peek().isLoopScope = stmt->isLoopBody;
    }
    else
    {
        // Comment out since Hoil starts without a scope
        // assert(false && 
        // "VisitCompoundStmt() received obj that's neither Stmt nor FuncDecl");
    }

    //stmt->list->Visit(this, stmt);
    stmt->list->Visit(this, obj); // Passing obj otherwise nested jump stmt fails

    symbolTable.CloseScope();

    return nullptr;
}

AST *Analyser::VisitWhileStmt(WhileStmt *stmt, AST *obj)
{
    stmt->cond->Visit(this, nullptr);
    stmt->isLoopStmt = true;
    stmt->stmt->Visit(this, stmt);

    if(!stmt->cond->isEmptyExpr && !(stmt->cond->type->IsBoolType() || stmt->cond->type->IsErrorType()))
    {
        ReportError("While conditional expr does not evaluate to bool");
        stmt->cond->type = std::move(std::make_unique<ErrorType>(stmt->cond->type->lineNo, stmt->cond->type->charNo));
    }

    return nullptr;
}

AST *Analyser::VisitCallStmt(CallStmt *stmt, AST *obj)
{
    // Same as VisitFuncCallExpr
    Decl *decl = symbolTable.Lookup(stmt->identifier->spelling);

    if(!decl || !decl->isFuncDecl)
    {
        std::ostringstream ss;
        ss << "Unknown Function Identifier: " << stmt->identifier->spelling;
        ReportError(ss.str());
    }
    else
    {
        stmt->args->Visit(this, dynamic_cast<FuncDecl*>(decl)->params.get());
    }

    return nullptr;
    return nullptr;
}

AST *Analyser::VisitInstructStmt(InstructStmt *stmt, AST *obj)
{
    stmt->literal->Visit(this, nullptr);
    return nullptr;
}

AST *Analyser::VisitDeclStmt(DeclStmt *stmt, AST *obj)
{
    stmt->decl->Visit(this, nullptr);
    return nullptr;
}

AST *Analyser::VisitForStmt(ForStmt *stmt, AST *obj)
{
    // HOIL only supports for loops
    stmt->isLoopStmt = true;
    symbolTable.OpenScope();    // TODO: Consider refactoring this
    stmt->list->Visit(this, stmt);
    stmt->cond->Visit(this, stmt);
    stmt->postOp->Visit(this, stmt);
    stmt->body->Visit(this, stmt);
    symbolTable.CloseScope();

    ExprStmt *condStmt = dynamic_cast<ExprStmt*>(stmt->cond.get());
    assert(condStmt && 
    "Conditional stmt for the ForStmt does not evaluate to ExprStmt");

    if(!(!condStmt->expr->type || condStmt->expr->type->IsBoolType() || condStmt->expr->type->IsErrorType()))
    {
        ReportError("For conditional expr does not evaluate to bool");
        condStmt->expr->type = std::move(std::make_unique<ErrorType>(condStmt->expr->type->lineNo, condStmt->expr->type->charNo));
    }



    return nullptr;
    
}

AST *Analyser::VisitDoWhileStmt(DoWhileStmt *stmt, AST *obj)
{
    // HOIL only supports while loops
    stmt->isLoopStmt = true;
    stmt->body->Visit(this, stmt);
    stmt->cond->Visit(this, nullptr);

    if(!(stmt->cond->type->IsBoolType() || stmt->cond->type->IsErrorType()))
    {
        ReportError("Do While conditional expr does not evaluate to bool");
        stmt->cond->type = std::move(std::make_unique<ErrorType>(stmt->cond->type->lineNo, stmt->cond->type->charNo));
    }

    return nullptr;
}

AST *Analyser::VisitIfStmt(IfStmt *stmt, AST *obj)
{
    stmt->cond->Visit(this, nullptr);

    if(!(stmt->cond->type->IsBoolType() || stmt->cond->type->IsErrorType()))
    {
        ReportError("If conditional expr does not evaluate to bool");
        stmt->cond->type = std::move(std::make_unique<ErrorType>(stmt->cond->type->lineNo, stmt->cond->type->charNo));
    }

    stmt->ifStmt->Visit(this, obj);
    stmt->elifList->Visit(this, obj);
    stmt->elseStmt->Visit(this, obj);

    return nullptr;
}

AST *Analyser::VisitElifStmt(ElifStmt *stmt, AST *obj)
{
    stmt->cond->Visit(this, nullptr);

    if(!(stmt->cond->type->IsBoolType() || stmt->cond->type->IsErrorType()))
    {
        ReportError("Elif conditional expr does not evaluate to bool");
        stmt->cond->type = std::move(std::make_unique<ErrorType>(stmt->cond->type->lineNo, stmt->cond->type->charNo));
    }

    stmt->stmt->Visit(this, obj);
    return nullptr;
}

AST *Analyser::VisitEmptyStmt(EmptyStmt *stmt, AST *obj)
{
    return nullptr;
}

AST *Analyser::VisitErrorStmt(ErrorStmt *stmt, AST *obj)
{
    return nullptr;
}

AST *Analyser::VisitExprStmt(ExprStmt *stmt, AST *obj)
{
    stmt->expr->Visit(this, nullptr);
    return nullptr;
}

// Function args
AST *Analyser::VisitArgList(ArgList *list, AST *obj)
{

    assert(obj && "No list passed to VisitArgList?");

    if(ParamList *paramList = dynamic_cast<ParamList*>(obj))
    {
        list->arg->Visit(this, paramList->param.get());
        list->next->Visit(this, paramList->next.get());
    }
    else if(EmptyParamList *paramList = dynamic_cast<EmptyParamList*>(obj))
    {
        ReportError("Expected less arguments!");
    }
    else
    {
        assert(false && "VisitArgList() couldn't typecast obj to EmptyParamList or ParamList.");
    }

    return nullptr;
}

AST *Analyser::VisitArg(Arg *arg, AST *obj)
{

    Param *param;
    assert(obj && "Nothing has been passed to VisitArg()? Expect Param.");
    assert((param = dynamic_cast<Param*>(obj)) 
    && "Obj passed to VisitArg() is not Param?");


    arg->expr->Visit(this, nullptr);
    
    if(!param->type->IsVoidType() && !arg->expr->type->Compatible(param->type.get()))
    {
        std::ostringstream ss;
        ss << "Argument type mismatch: " << param->identifier->spelling;
        ReportError(ss.str());
    }


    return nullptr;
}

AST *Analyser::VisitBlockItemList(BlockItemList *list, AST *obj)
{
    list->block->Visit(this, obj);
    list->next->Visit(this, obj);
    return nullptr;
}

AST *Analyser::VisitElifList(ElifList *list, AST *obj)
{
    list->elif->Visit(this, obj);
    list->next->Visit(this, obj);
    return nullptr;
}

AST *Analyser::VisitEmptyArgList(EmptyArgList *list, AST *obj)
{
    assert(obj && "VisitEmptyArgList() received nullptr.");

    if(EmptyParamList *param = dynamic_cast<EmptyParamList*>(obj))
    {
        
    }
    else if(ParamList *param = dynamic_cast<ParamList*>(obj))
    {
        ReportError("Argument list mismatch, expect more arguments");
    }
    else
    {
        assert(false && "VisitEmptyArgList() couldn't convert obj to ParamList or EmptyParamList");
    }

    return nullptr;
}

AST *Analyser::VisitEmptyBlockList(EmptyBlockList *list, AST *obj)
{
    return nullptr;
}

AST *Analyser::VisitEmptyElifList(EmptyElifList *list, AST *obj)
{
    return nullptr;
}

AST *Analyser::VisitEmptyVarDeclList(EmptyVarDeclList *list, AST *obj)
{
    return nullptr;
}

AST *Analyser::VisitEmptyFuncDeclList(EmptyFuncDeclList *list, AST *obj)
{
return nullptr;
}

AST *Analyser::VisitEmptyParamList(EmptyParamList *list, AST *obj)
{
    return nullptr;
}

AST *Analyser::VisitParamList(ParamList *list, AST *obj)
{
    list->param->Visit(this, obj);
    list->next->Visit(this, obj);
    return nullptr;
}

AST *Analyser::VisitParam(Param *param, AST *obj)
{
    param->isParamDecl = true;
    if(!symbolTable.Insert(param->identifier->spelling, param))
    {
        std::ostringstream ss;
        ss << "Trying to declare a param. Identifier exists: " << param->identifier->spelling;
        ReportError(ss.str());
    }

    return nullptr;
}

AST *Analyser::VisitStmtBlock(StmtBlock *block, AST *obj)
{
    block->stmt->Visit(this, obj);
    return nullptr;
}

AST *Analyser::VisitVarDeclListBlock(VarDeclListBlock *block, AST *obj)
{
    block->list->Visit(this, obj);
    return nullptr;
}

AST *Analyser::VisitVarDeclList(VarDeclList *list, AST *obj)
{
    list->decl->Visit(this, obj);
    list->next->Visit(this, obj);
    return nullptr;
}

// Types
// No need to do anything regarding type checking:
// exprs and stmts will do instead.
AST *Analyser::VisitBoolType(BoolType *type, AST *obj) 
{
    return nullptr;
}

AST *Analyser::VisitErrorType(ErrorType *type, AST *obj)
{
    return nullptr;
}

AST *Analyser::VisitIntType(IntType *type, AST *obj)
{
    return nullptr;
}

AST *Analyser::VisitRealType(RealType *type, AST *obj)
{
    return nullptr;
}

AST *Analyser::VisitVoidType(VoidType *type, AST *obj)
{
    return nullptr;
}

AST *Analyser::VisitStringType(StringType *type, AST *obj)
{
    return nullptr;
}

AST *Analyser::VisitObjectType(ObjectType *type, AST *obj)
{
    return nullptr;
}

AST *Analyser::VisitAttributeType(AttributeType *type, AST *obj)
{
    return nullptr;
}

AST *Analyser::VisitBoolLiteral(BoolLiteral *literal, AST *obj)
{
    return nullptr;
}

AST *Analyser::VisitIntLiteral(IntLiteral *literal, AST *obj)
{
    return nullptr;
}

AST *Analyser::VisitRealLiteral(RealLiteral *literal, AST *obj)
{
    return nullptr;
}

AST *Analyser::VisitStringLiteral(StringLiteral *literal, AST *obj)
{
    return nullptr;
}

AST *Analyser::VisitOperator(Operator *op, AST *obj)
{
    return nullptr;
}

AST *Analyser::VisitVariable(Variable *variable, AST *obj)
{
    return nullptr;
}

AST *Analyser::VisitIdentifier(Identifier *ident, AST *obj)
{
    return nullptr;
}

AST *Analyser::VisitProgram(Program *program, AST *obj)
{
    program->list->Visit(this, nullptr);
    return nullptr;
}











