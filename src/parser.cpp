#include <sstream>
#include "lexer.h"
#include "parser.h"

using namespace Lexicons;

Parser::Parser(Lexer *lexer) : lexer{lexer}
{
    Next(); // Grab the first token
    ParseProgram();
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


void Parser::ParseProgram()
{
    while(
        LexemeIs(Lexicon::INT)  ||
        LexemeIs(Lexicon::REAL) ||
        LexemeIs(Lexicon::BOOL) ||
        LexemeIs(Lexicon::STRING) ||
        LexemeIs(Lexicon::VOID)
        )
    {
        ParseFuncDecl();
    }

    Match(Lexicon::END_OF_FILE);
}

void Parser::ParseVarDecl()
{
    ParseType();
    ParseVarDeclList();
    Match(Lexicon::SEMICOLON);
}

void Parser::ParseVarDeclList()
{
    ParseVarDeclExpr();
    while(currentLexicon->Id == Lexicon::COMMA)
    {
        Next();
        ParseVarDeclList();
    }
}

void Parser::ParseVarDeclExpr()
{
    Match(Lexicon::IDENTIFIER);

    if(currentLexicon->Id == Lexicon::ASSIGN)
    {
        Next();
        ParseExpr();
    }
}

void Parser::ParseFuncDecl()
{
    ParseType();
    Match(Lexicon::IDENTIFIER);

    Match(Lexicon::OPAREN);

    if(!LexemeIs(Lexicon::CPAREN))
    {
        ParseParamList();
    }

    Match(Lexicon::CPAREN);

    ParseCompoundStmt();
}

void Parser::ParseParamList()
{
    ParseParam();
    while(LexemeIs(Lexicon::COMMA))
    {
        Next();
        ParseParam();
    }
}

void Parser::ParseParam()
{
    ParseType();
    Match(Lexicon::IDENTIFIER);
}

std::unique_ptr<ASTs::ArgList> Parser::ParseArgList()
{
    // TODO: Update
    ParseArg();
    while(LexemeIs(Lexicon::COMMA))
    {
        Next();
        ParseArg();
    }

    return nullptr;
}

std::unique_ptr<ASTs::Arg> Parser::ParseArg()
{
    // TODO: Update
    ParseExpr();
    
    return nullptr;
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

void Parser::ParseExpr()
{
    ParseAssignmentExpr();
}

void Parser::ParseAssignmentExpr()
{
    ParseLogicalOrExpr();

    while(LexemeIs(Lexicon::ASSIGN) ||
        LexemeIs(Lexicon::ADD_ASSIGN)||
        LexemeIs(Lexicon::SUB_ASSIGN)||
        LexemeIs(Lexicon::MUL_ASSIGN)||
        LexemeIs(Lexicon::DIV_ASSIGN))
        {
            Next();
            ParseLogicalOrExpr();
        }
}

void Parser::ParseLogicalOrExpr()
{
    ParseLogicalAndExpr();
    while(LexemeIs(Lexicon::LOGICAL_OR))
    {
        Next();
        ParseLogicalAndExpr();
    }
}

void Parser::ParseLogicalAndExpr()
{
    ParseEqualityExpr();
    while(LexemeIs(Lexicon::LOGICAL_AND))
    {
        Next();
        ParseEqualityExpr();
    }
}

void Parser::ParseEqualityExpr()
{
    ParseRelationExpr();
    while(LexemeIs(Lexicon::EQUAL) || LexemeIs(Lexicon::NEQUAL))
    {
        Next();
        ParseRelationExpr();
    }
}

void Parser::ParseRelationExpr()
{
    ParseAdditiveExpr();
    while(
        LexemeIs(Lexicon::LESS) || LexemeIs(Lexicon::LEQUAL) ||
        LexemeIs(Lexicon::GREATER) || LexemeIs(Lexicon::GEQUAL))
    {
        Next();
        ParseAdditiveExpr();
    }
}

void Parser::ParseAdditiveExpr()
{
    ParseMultiplicativeExpr();

    while(LexemeIs(Lexicon::ADD) || LexemeIs(Lexicon::SUB))
    {
        Next();
        ParseMultiplicativeExpr();
    }

}

void Parser::ParseMultiplicativeExpr()
{
    ParseUnaryExpr();

    while(LexemeIs(Lexicon::MUL) || 
          LexemeIs(Lexicon::DIV) || 
          LexemeIs(Lexicon::MOD))
    {
        Next();
        ParseUnaryExpr();
    }
}

void Parser::ParseUnaryExpr()
{  
    if(LexemeIs(Lexicon::UNARY_ADD))
    {
        Next();
        ParseUnaryExpr();
    }
    else if(LexemeIs(Lexicon::ADD))
    {
        Next();
        ParseUnaryExpr();
    }
    else if(LexemeIs(Lexicon::UNARY_SUB))
    {
        Next();
        ParseUnaryExpr();
    }
    else if(LexemeIs(Lexicon::SUB))
    {
        Next();
        ParseUnaryExpr();
    }
    else if(LexemeIs(Lexicon::NOT))
    {
        Next();
        ParseUnaryExpr();
    }
    else
    {
        ParsePrimaryExpr();
    }
}

void Parser::ParsePrimaryExpr()
{
    std::unique_ptr<ASTs::Expr> expr{};

    if(LexemeIs(Lexicon::IDENTIFIER))
    {
        auto identifier = ParseIdentifier();

        // Check function call, post ++ or --
        if(LexemeIs(Lexicon::OPAREN))
        {
            // TODO: Handle function call
            Next();
            if(!LexemeIs(Lexicon::CPAREN))
            {
                ParseArgList();
            }

            Match(Lexicon::CPAREN);
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
        ParseExpr();
        Match(Lexicon::CPAREN);
    }
    else
    {
        ReportMismatch();
    }
}

void Parser::ParseStmt()
{
    // TODO: Calculate first sets
    if(LexemeIs(Lexicon::IF))
    {
        ParseIfStmt();
    }
    else if(LexemeIs(Lexicon::LOOP))
    {
        ParseLoopStmt();
    }
    else if(LexemeIs(Lexicon::CONTINUE) || LexemeIs(Lexicon::BREAK))
    {
        ParseJumpStmt();
    }
    else if(LexemeIs(Lexicon::RETURN))
    {
        ParseReturnStmt();
    }
    else if(LexemeIs(Lexicon::OCURLY))
    {
        ParseCompoundStmt();
    }
    else
    {
        ParseExprStmt();
    }
}

void Parser::ParseExprStmt()
{
    if(LexemeIs(Lexicon::SEMICOLON))
    {
        Next();
    }
    else
    {
        ParseExpr();
        Match(Lexicon::SEMICOLON);
    }
}

void Parser::ParseIfStmt()
{
    Match(Lexicon::IF);

    Match(Lexicon::OPAREN);
    ParseExpr();
    Match(Lexicon::CPAREN);

    ParseStmt();

    while(LexemeIs(Lexicon::ELIF))
    {
        Next();

        Match(Lexicon::OPAREN);
        ParseExpr();
        Match(Lexicon::CPAREN);

        ParseStmt();
    }

    if(LexemeIs(Lexicon::ELSE))
    {
        Next();

        ParseStmt();
    }

}

void Parser::ParseLoopStmt()
{
    Match(Lexicon::LOOP);
    if(!LexemeIs(Lexicon::OPAREN))
    {
        // Handle LOOP UNTIL
        ParseStmt();
        Match(Lexicon::UNTIL);
        Match(Lexicon::OPAREN);
        ParseExpr();
        Match(Lexicon::CPAREN);
        Match(Lexicon::SEMICOLON);
    }
    else
    {
        Match(Lexicon::OPAREN);
        if(LexemeIs(Lexicon::INT) || LexemeIs(Lexicon::REAL) || 
        LexemeIs(Lexicon::STRING) || LexemeIs(Lexicon:: VOID))
        {
            // For-loop like form
            ParseVarDecl();
            ParseExprStmt();
            ParseExpr();

        }
        else
        {
            // While-loop like form
            ParseExpr();
        }

        Match(Lexicon::CPAREN);
        ParseStmt();
    }
}

void Parser::ParseJumpStmt()
{
    if(LexemeIs(Lexicon::CONTINUE))
    {
        Next();
    }
    else
    {
        Match(Lexicon::BREAK);
    }

    Match(Lexicon::SEMICOLON);
}

void Parser::ParseReturnStmt()
{
    Match(Lexicon::RETURN);
    ParseExprStmt();
}

void Parser::ParseCompoundStmt()
{
    Match(Lexicon::OCURLY);

    if(!LexemeIs(Lexicon::CCURLY))
    {
        ParseItemList();
    }

    Match(Lexicon::CCURLY);
}


void Parser::ParseItemList()
{
    ParseItem();
    // TODO: STOP BEING LAZY AND IMPLEMENT FIRST SET
    // WHAT IS THIS??????
    while(
        LexemeIs(Lexicon::INT) || LexemeIs(Lexicon::REAL) || LexemeIs(Lexicon::STRING) || LexemeIs(Lexicon::VOID) || LexemeIs(Lexicon::BOOL)
    ||  LexemeIs(Lexicon::IF) || LexemeIs(Lexicon::LOOP) || LexemeIs(Lexicon::CONTINUE) || LexemeIs(Lexicon::BREAK)
    ||  LexemeIs(Lexicon::RETURN) || LexemeIs(Lexicon::OCURLY) || LexemeIs(Lexicon::IDENTIFIER) || LexemeIs(Lexicon::INTVAL)
    ||  LexemeIs(Lexicon::REALVAL) || LexemeIs(Lexicon::BOOLVAL) || LexemeIs(Lexicon::STRINGVAL) || LexemeIs(Lexicon::OPAREN)
    ||  LexemeIs(Lexicon::ADD) || LexemeIs(Lexicon::SUB) || LexemeIs(Lexicon::UNARY_ADD) || LexemeIs(Lexicon::UNARY_SUB)
    ||  LexemeIs(Lexicon::NOT))
    {
        ParseItem();
    }

}

void Parser::ParseItem()
{
    if(LexemeIs(Lexicon::INT)  ||
        LexemeIs(Lexicon::REAL) ||
        LexemeIs(Lexicon::BOOL) ||
        LexemeIs(Lexicon::STRING) ||
        LexemeIs(Lexicon::VOID))
    {
        ParseVarDecl();
    }
    else
    {
        ParseStmt();
    }
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