#include <sstream>
#include "lexer.h"
#include "parser.h"

using namespace Lexicons;

Parser::Parser(Lexer *lexer) : lexer{lexer}
{
    Next(); // Grab the first token
    program = ParseProgram();
}

void Parser::Next()
{
    currentLexicon = lexer->GetLexicon();
}

bool Parser::LexemeIs(Lexicons::LexiconId id)
{
    return currentLexicon->Id == id;
}

void Parser::Match(Lexicons::LexiconId id)
{
    if(currentLexicon->Id != id)
    {
        ReportMismatch();
    }
    else
    {
        Next();
    }

}

void Parser::ReportMismatch()
{
    std::ostringstream ss;
    ss << "Unexpected Token: " << currentLexicon->Verbose();
    errorMsgs.push_back(ss.str());
    //Next();
}


std::unique_ptr<ASTs::Program> Parser::ParseProgram()
{
    std::unique_ptr<ASTs::List> list = std::make_unique<ASTs::EmptyFuncDeclList>();
    if( LexemeIs(Lexicon::INT)  ||
        LexemeIs(Lexicon::REAL) ||
        LexemeIs(Lexicon::BOOL) ||
        LexemeIs(Lexicon::STRING) ||
        LexemeIs(Lexicon::VOID))
    {
        list = ParseFuncDeclList();
    }

    Match(Lexicon::END_OF_FILE);

    return std::make_unique<ASTs::Program>(list.release());
}

std::unique_ptr<ASTs::Decl> Parser::ParseVarDecl()
{
    auto type = ParseType();
    auto list = ParseVarDeclList();
    Match(Lexicon::SEMICOLON);

    return std::make_unique<ASTs::VarDecl>(type.release(), list.release());
}

std::unique_ptr<ASTs::List> Parser::ParseVarDeclList()
{
    auto expr = ParseVarDeclExpr();
    std::unique_ptr<ASTs::List> next = std::make_unique<ASTs::EmptyVarDeclList>();
    if(currentLexicon->Id == Lexicon::COMMA)
    {
        Next();
        next = ParseVarDeclList();
    }

    return std::make_unique<ASTs::VarDeclList>(expr.release(), next.release());
}

std::unique_ptr<ASTs::Expr> Parser::ParseVarDeclExpr()
{
    auto ident = ParseIdentifier();
    std::unique_ptr<ASTs::Expr> expr = std::make_unique<ASTs::EmptyExpr>();
    if(currentLexicon->Id == Lexicon::ASSIGN)
    {
        Next();
        expr = ParseExpr();
    }

    return std::make_unique<ASTs::VarDeclExpr>(ident.release(), expr.release());
}

std::unique_ptr<ASTs::List> Parser::ParseFuncDeclList()
{
    auto decl = ParseFuncDecl();
    std::unique_ptr<ASTs::List> list = std::unique_ptr<ASTs::EmptyFuncDeclList>();

    if( LexemeIs(Lexicon::INT)  ||
        LexemeIs(Lexicon::REAL) ||
        LexemeIs(Lexicon::BOOL) ||
        LexemeIs(Lexicon::STRING) ||
        LexemeIs(Lexicon::VOID))
    {
        list = ParseFuncDeclList();
    }

    return std::make_unique<ASTs::FuncDeclList>(decl.release(), list.release());
}

std::unique_ptr<ASTs::Decl> Parser::ParseFuncDecl()
{
    auto type = ParseType();
    auto ident = ParseIdentifier();

    Match(Lexicon::OPAREN);

    std::unique_ptr<ASTs::List> params = std::make_unique<ASTs::EmptyParamList>();
    if(!LexemeIs(Lexicon::CPAREN))
    {
        params = ParseParamList();
    }

    Match(Lexicon::CPAREN);

    auto stmt = ParseCompoundStmt();

    return std::make_unique<ASTs::FuncDecl>(type.release(), ident.release(), params.release(), stmt.release());
}

std::unique_ptr<ASTs::List> Parser::ParseParamList()
{
    auto param = ParseParam();
    std::unique_ptr<ASTs::List> paramList{};
    if(LexemeIs(Lexicon::COMMA))
    {
        Next();
        paramList = ParseParamList();
    }
    else
    {
        paramList = std::make_unique<ASTs::EmptyParamList>();
    }

    return std::make_unique<ASTs::ParamList>(param.release(), paramList.release());
}

std::unique_ptr<ASTs::Param> Parser::ParseParam()
{
    auto type = ParseType();
    auto iden = ParseIdentifier();

    return std::make_unique<ASTs::Param>(type.release(), iden.release());
}

std::unique_ptr<ASTs::List> Parser::ParseArgList()
{
    std::unique_ptr<ASTs::ArgList> list{};
    auto arg = ParseArg();
    if(LexemeIs(Lexicon::COMMA))
    {
        Next();
        auto list2 = ParseArgList();

        list = std::make_unique<ASTs::ArgList>(arg.release(), list2.release());
    }
    else
    {
        list = std::make_unique<ASTs::ArgList>(arg.release(), new ASTs::EmptyArgList());
    }

    return list;
}

std::unique_ptr<ASTs::Arg> Parser::ParseArg()
{
    return std::make_unique<ASTs::Arg>(ParseExpr().release());
}

std::unique_ptr<ASTs::Type> Parser::ParseType()
{
    std::unique_ptr<ASTs::Type> ptr{};
    switch(currentLexicon->Id)
    {
        case Lexicon::INT:
        Next();
        ptr = std::make_unique<ASTs::IntType>();
        break;
        case Lexicon::REAL:
        Next();
        ptr = std::make_unique<ASTs::RealType>();
        break;
        case Lexicon::BOOL:
        Next();
        ptr = std::make_unique<ASTs::BoolType>();
        break;
        case Lexicon::VOID:
        Next();
        ptr = std::make_unique<ASTs::VoidType>();
        break;
        case Lexicon::STRING:
        Next();
        ptr = std::make_unique<ASTs::StringType>();
        break;
        default:
        ReportMismatch();
    }
    return ptr;
}

std::unique_ptr<ASTs::Expr> Parser::ParseExpr()
{
    return ParseAssignmentExpr();
}

std::unique_ptr<ASTs::Expr> Parser::ParseAssignmentExpr()
{
    std::unique_ptr<ASTs::Expr> expr1 = ParseLogicalOrExpr();

    while(LexemeIs(Lexicon::ASSIGN) ||
        LexemeIs(Lexicon::ADD_ASSIGN)||
        LexemeIs(Lexicon::SUB_ASSIGN)||
        LexemeIs(Lexicon::MUL_ASSIGN)||
        LexemeIs(Lexicon::DIV_ASSIGN))
        {
            auto op = ParseOperator();
            auto expr2 = ParseLogicalOrExpr();

            expr1 = std::make_unique<ASTs::AssignExpr>(expr1.release(), expr2.release(), op.release());
        }

    return expr1;
}

std::unique_ptr<ASTs::Expr> Parser::ParseLogicalOrExpr()
{
    std::unique_ptr<ASTs::Expr> expr1 = ParseLogicalAndExpr();
    while(LexemeIs(Lexicon::LOGICAL_OR))
    {
        auto op = ParseOperator();
        auto expr2 = ParseLogicalAndExpr();
        expr1 = std::make_unique<ASTs::BinaryExpr>(expr1.release(), expr2.release(), op.release());
    }

    return expr1;
}

std::unique_ptr<ASTs::Expr> Parser::ParseLogicalAndExpr()
{
    std::unique_ptr<ASTs::Expr> expr1 = ParseEqualityExpr();
    while(LexemeIs(Lexicon::LOGICAL_AND))
    {
        auto op = ParseOperator();
        auto expr2 = ParseEqualityExpr();
        expr1 = std::make_unique<ASTs::BinaryExpr>(expr1.release(), expr2.release(), op.release());
    }

    return expr1;
}

std::unique_ptr<ASTs::Expr> Parser::ParseEqualityExpr()
{
    std::unique_ptr<ASTs::Expr> expr1 = ParseRelationExpr();

    while(LexemeIs(Lexicon::EQUAL) || LexemeIs(Lexicon::NEQUAL))
    {
        auto op = ParseOperator();
        auto expr2 = ParseRelationExpr();
        expr1 = std::make_unique<ASTs::BinaryExpr>(expr1.release(), expr2.release(), op.release());
    }

    return expr1;
}

std::unique_ptr<ASTs::Expr> Parser::ParseRelationExpr()
{
    std::unique_ptr<ASTs::Expr> expr1 = ParseAdditiveExpr();

    while(
        LexemeIs(Lexicon::LESS) || LexemeIs(Lexicon::LEQUAL) ||
        LexemeIs(Lexicon::GREATER) || LexemeIs(Lexicon::GEQUAL))
    {
        auto op = ParseOperator();
        auto expr2 = ParseAdditiveExpr();
        expr1 = std::make_unique<ASTs::BinaryExpr>(expr1.release(), expr2.release(), op.release());
    }

    return expr1;
}

std::unique_ptr<ASTs::Expr> Parser::ParseAdditiveExpr()
{
    std::unique_ptr<ASTs::Expr> expr1 = ParseMultiplicativeExpr();

    while(LexemeIs(Lexicon::ADD) || LexemeIs(Lexicon::SUB))
    {
        auto op = ParseOperator();
        auto expr2 = ParseMultiplicativeExpr();

        expr1 = std::make_unique<ASTs::BinaryExpr>(expr1.release(), expr2.release(), op.release());
    }

    return expr1;
}

std::unique_ptr<ASTs::Expr> Parser::ParseMultiplicativeExpr()
{
    std::unique_ptr<ASTs::Expr> expr1 = ParseUnaryExpr();

    while(LexemeIs(Lexicon::MUL) || 
          LexemeIs(Lexicon::DIV) || 
          LexemeIs(Lexicon::MOD))
    {
        auto op = ParseOperator();
        auto expr2 = ParseUnaryExpr();
        expr1 = std::make_unique<ASTs::BinaryExpr>(expr1.release(), expr2.release(), op.release());
    }
    return expr1;
}

std::unique_ptr<ASTs::Expr> Parser::ParseUnaryExpr()
{  
    if( LexemeIs(Lexicon::UNARY_ADD) || LexemeIs(Lexicon::ADD) || LexemeIs(Lexicon::UNARY_SUB) 
     || LexemeIs(Lexicon::SUB)       || LexemeIs(Lexicon::NOT))
    {
        auto op = ParseOperator();
        auto expr2 = ParseUnaryExpr();

        return std::make_unique<ASTs::PreUnaryExpr>(expr2.release(), op.release());
    }
    else
    {
        return ParsePrimaryExpr();
    }
}

std::unique_ptr<ASTs::Expr> Parser::ParsePrimaryExpr()
{
    std::unique_ptr<ASTs::Expr> expr{};

    if(LexemeIs(Lexicon::IDENTIFIER))
    {
        auto identifier = ParseIdentifier();

        // Check function call, post ++ or --
        if(LexemeIs(Lexicon::OPAREN))
        {
            Next();
            ASTs::List *argList = nullptr;
            if(!LexemeIs(Lexicon::CPAREN))
            {
                argList = ParseArgList().release();
            }
            else
            {
                argList = new ASTs::EmptyArgList();
            }
            Match(Lexicon::CPAREN);

            expr = std::make_unique<ASTs::FunctionCallExpr>(identifier.release(), argList);
        }
        else if(LexemeIs(Lexicon::UNARY_ADD) || LexemeIs(Lexicon::UNARY_SUB))
        {
            auto op = ParseOperator();
            auto var = new ASTs::VariableExpr(new ASTs::Variable(identifier.release()));

            expr = std::make_unique<ASTs::PostUnaryExpr>(var, op.release());
        }
        else
        {
            expr = std::make_unique<ASTs::VariableExpr>(new ASTs::Variable(identifier.release()));
        }
    }
    else if(LexemeIs(Lexicon::INTVAL))
    {
        auto intLiteral = ParseIntLiteral();
        expr = std::make_unique<ASTs::IntExpr>(intLiteral.release());
    }
    else if(LexemeIs(Lexicon::REALVAL))
    {
        auto realLiteral = ParseRealLiteral();
        expr = std::make_unique<ASTs::RealExpr>(realLiteral.release());
    }
    else if(LexemeIs(Lexicon::BOOLVAL))
    {
        auto boolLiteral = ParseBoolLiteral();
        expr = std::make_unique<ASTs::BoolExpr>(boolLiteral.release());
    }
    else if(LexemeIs(Lexicon::STRINGVAL))
    {
        auto stringLiteral = ParseStringLiteral();
        expr = std::make_unique<ASTs::StringExpr>(stringLiteral.release());
    }
    else if(LexemeIs(Lexicon::OPAREN))
    {
        Next();
        expr = ParseExpr();
        Match(Lexicon::CPAREN);
    }
    else
    {
        ReportMismatch();
    }

    return expr;
}

std::unique_ptr<ASTs::Stmt> Parser::ParseStmt()
{
    if(LexemeIs(Lexicon::IF))
    {
        return ParseIfStmt();
    }
    else if(LexemeIs(Lexicon::LOOP))
    {
        return ParseLoopStmt();
    }
    else if(LexemeIs(Lexicon::CONTINUE) || LexemeIs(Lexicon::BREAK))
    {
        return ParseJumpStmt();
    }
    else if(LexemeIs(Lexicon::RETURN))
    {
        return ParseReturnStmt();
    }
    else if(LexemeIs(Lexicon::OCURLY))
    {
        return ParseCompoundStmt();
    }
    else
    {
        return ParseExprStmt();
    }
}

std::unique_ptr<ASTs::Stmt> Parser::ParseExprStmt()
{
    if(LexemeIs(Lexicon::SEMICOLON))
    {
        Next();
        return std::make_unique<ASTs::EmptyStmt>();
    }
    else
    {
        auto expr = ParseExpr();
        Match(Lexicon::SEMICOLON);

        return std::make_unique<ASTs::ExprStmt>(expr.release());
    }
}

std::unique_ptr<ASTs::Stmt> Parser::ParseIfStmt()
{
    Match(Lexicon::IF);

    Match(Lexicon::OPAREN);
    auto ifCond = ParseExpr();
    Match(Lexicon::CPAREN);

    auto ifBody = ParseStmt();

    std::unique_ptr<ASTs::List> elifList{};
    if(LexemeIs(Lexicon::ELIF))
    {
        elifList = ParseElifList();
    }
    else
    {
        elifList = std::make_unique<ASTs::EmptyElifList>();
    }


    std::unique_ptr<ASTs::Stmt> elseStmt{};
    if(LexemeIs(Lexicon::ELSE))
    {
        Next();
        elseStmt = ParseStmt();
    }
    else
    {
        elseStmt = std::make_unique<ASTs::EmptyStmt>();
    }

    return std::make_unique<ASTs::IfStmt>(ifCond.release(), ifBody.release(), elifList.release(), elseStmt.release());
}

std::unique_ptr<ASTs::List> Parser::ParseElifList()
{
    Match(Lexicon::ELIF);
    Match(Lexicon::OPAREN);

    auto cond = ParseExpr();
    Match(Lexicon::CPAREN);

    auto stmt = ParseStmt();

    std::unique_ptr<ASTs::ElifStmt> elif = std::make_unique<ASTs::ElifStmt>(cond.release(), stmt.release());

    if(LexemeIs(Lexicon::ELIF))
    {
        auto list = ParseElifList();
        return std::make_unique<ASTs::ElifList>(elif.release(), list.release());
    }
    else
    {
        return std::make_unique<ASTs::ElifList>(elif.release(), new ASTs::EmptyElifList());
    }


}

std::unique_ptr<ASTs::Stmt> Parser::ParseLoopStmt()
{
    std::unique_ptr<ASTs::Stmt> stmt{};

    Match(Lexicon::LOOP);
    if(!LexemeIs(Lexicon::OPAREN))
    {
        // Handle LOOP UNTIL
        auto body = ParseStmt();
        Match(Lexicon::UNTIL);
        Match(Lexicon::OPAREN);
        auto cond = ParseExpr();
        Match(Lexicon::CPAREN);
        Match(Lexicon::SEMICOLON);

        stmt = std::make_unique<ASTs::DoWhileStmt>(cond.release(), body.release());
    }
    else
    {
        Match(Lexicon::OPAREN);

        if(LexemeIs(Lexicon::INT) || LexemeIs(Lexicon::REAL) || 
        LexemeIs(Lexicon::STRING) || LexemeIs(Lexicon:: VOID))
        {
            // For-loop like form
            auto decl = ParseVarDecl();
            auto cond = ParseExprStmt();
            auto postOp = ParseExpr();
            Match(Lexicon::CPAREN);

            auto body = ParseStmt();

            stmt = std::make_unique<ASTs::ForStmt>(decl.release(), cond.release(), postOp.release(), body.release());

        }
        else
        {
            // While-loop like form
            auto cond = ParseExpr();
            Match(Lexicon::CPAREN);
            auto body = ParseStmt();

            stmt = std::make_unique<ASTs::WhileStmt>(cond.release(), body.release());
        }

    }

    return stmt;
}

std::unique_ptr<ASTs::Stmt> Parser::ParseJumpStmt()
{
    std::unique_ptr<ASTs::Stmt> stmt{};
    if(LexemeIs(Lexicon::CONTINUE))
    {
        Next();
        stmt = std::make_unique<ASTs::ContinueStmt>();
    }
    else
    {
        Match(Lexicon::BREAK);
        stmt = std::make_unique<ASTs::BreakStmt>();

    }

    Match(Lexicon::SEMICOLON);
    return stmt;
}

std::unique_ptr<ASTs::Stmt> Parser::ParseReturnStmt()
{
    Match(Lexicon::RETURN);
    return std::make_unique<ASTs::ReturnStmt>(ParseExprStmt().release());
}

std::unique_ptr<ASTs::Stmt> Parser::ParseCompoundStmt()
{
    Match(Lexicon::OCURLY);
    std::unique_ptr<ASTs::List> list = std::unique_ptr<ASTs::EmptyBlockList>();
    if(!LexemeIs(Lexicon::CCURLY))
    {
        list = ParseItemList();
    }

    Match(Lexicon::CCURLY);
    return std::make_unique<ASTs::CompoundStmt>(list.release());
}


std::unique_ptr<ASTs::List> Parser::ParseItemList()
{
    auto item = ParseItem();
    std::unique_ptr<ASTs::List> blockList = std::make_unique<ASTs::EmptyBlockList>();
    // TODO: STOP BEING LAZY AND IMPLEMENT FIRST SET
    // WHAT IS THIS??????
    if(
        LexemeIs(Lexicon::INT) || LexemeIs(Lexicon::REAL) || LexemeIs(Lexicon::STRING) || LexemeIs(Lexicon::VOID) || LexemeIs(Lexicon::BOOL)
    ||  LexemeIs(Lexicon::IF) || LexemeIs(Lexicon::LOOP) || LexemeIs(Lexicon::CONTINUE) || LexemeIs(Lexicon::BREAK)
    ||  LexemeIs(Lexicon::RETURN) || LexemeIs(Lexicon::OCURLY) || LexemeIs(Lexicon::IDENTIFIER) || LexemeIs(Lexicon::INTVAL)
    ||  LexemeIs(Lexicon::REALVAL) || LexemeIs(Lexicon::BOOLVAL) || LexemeIs(Lexicon::STRINGVAL) || LexemeIs(Lexicon::OPAREN)
    ||  LexemeIs(Lexicon::ADD) || LexemeIs(Lexicon::SUB) || LexemeIs(Lexicon::UNARY_ADD) || LexemeIs(Lexicon::UNARY_SUB)
    ||  LexemeIs(Lexicon::NOT))
    {
        blockList = ParseItemList();
    }

    return std::make_unique<ASTs::BlockItemList>(item.release(), blockList.release());
}

std::unique_ptr<ASTs::Block> Parser::ParseItem()
{
    std::unique_ptr<ASTs::Block> block{};
    if(LexemeIs(Lexicon::INT)  ||
        LexemeIs(Lexicon::REAL) ||
        LexemeIs(Lexicon::BOOL) ||
        LexemeIs(Lexicon::STRING) ||
        LexemeIs(Lexicon::VOID))
    {
        auto decl = ParseVarDecl();
        block = std::make_unique<ASTs::VarDeclBlock>(decl.release());
    }
    else
    {
        auto stmt = ParseStmt();
        block = std::make_unique<ASTs::StmtBlock>(stmt.release());
    }

    return block;
}

std::unique_ptr<ASTs::Operator> Parser::ParseOperator()
{
    // TODO: Handle
    auto op = std::make_unique<ASTs::Operator>(currentLexicon->spelling);
    Next();
    return op;
}

std::unique_ptr<ASTs::IntLiteral> Parser::ParseIntLiteral()
{
    if(!LexemeIs(Lexicon::INTVAL))
        return std::unique_ptr<ASTs::IntLiteral>{};

    Next();
    return std::make_unique<ASTs::IntLiteral>(currentLexicon->spelling);
}

std::unique_ptr<ASTs::RealLiteral> Parser::ParseRealLiteral()
{
    if(!LexemeIs(Lexicon::REALVAL))
        return std::unique_ptr<ASTs::RealLiteral>{};

    Next();
    return std::make_unique<ASTs::RealLiteral>(currentLexicon->spelling);
}

std::unique_ptr<ASTs::BoolLiteral> Parser::ParseBoolLiteral()
{
    if(!LexemeIs(Lexicon::BOOLVAL))
        return std::unique_ptr<ASTs::BoolLiteral>{};

    Next();
    return std::make_unique<ASTs::BoolLiteral>(currentLexicon->spelling);
}

std::unique_ptr<ASTs::StringLiteral> Parser::ParseStringLiteral()
{
    if(!LexemeIs(Lexicon::STRINGVAL))
        return std::unique_ptr<ASTs::StringLiteral>{};

    Next();
    return std::make_unique<ASTs::StringLiteral>(currentLexicon->spelling);
}

std::unique_ptr<ASTs::Identifier> Parser::ParseIdentifier()
{
    if(!LexemeIs(Lexicon::IDENTIFIER))
        return std::unique_ptr<ASTs::Identifier>{};
    
    Next();
    return std::make_unique<ASTs::Identifier>(currentLexicon->spelling);
}