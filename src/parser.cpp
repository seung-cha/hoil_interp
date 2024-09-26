#include <sstream>
#include "lexer.h"
#include "parser.h"

using namespace Lexicons;

Parser::Parser(Lexer *lexer) : lexer{lexer}
{
    Next();
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
    Next();
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
        ParseVarDecl();
    }

    Match(Lexicon::END_OF_FILE);
}

void Parser::ParseVarDecl()
{
    // var_decl -> type var_decl_list ";"
    ParseType();
    ParseVarDeclList();
    Match(Lexicon::SEMICOLON);
}

void Parser::ParseVarDeclList()
{
    // var_decl_list -> var_decl_expr ("," var_decl_list)*
    ParseVarDeclExpr();
    while(currentLexicon->Id == Lexicon::COMMA)
    {
        Next();
        ParseVarDeclList();
    }
}

void Parser::ParseVarDeclExpr()
{
    // var_decl_expr -> _identifier_ ("=" var_init_expr)?
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
    ParseParamList();
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

void Parser::ParseArgList()
{
    ParseArg();
    while(LexemeIs(Lexicon::COMMA))
    {
        Next();
        ParseArg();
    }
}

void Parser::ParseArg()
{
    ParseExpr();
}

void Parser::ParseType()
{
    switch(currentLexicon->Id)
    {
        case Lexicon::INT:
        Next();
        break;
        case Lexicon::REAL:
        Next();
        break;
        case Lexicon::BOOL:
        Next();
        break;
        case Lexicon::VOID:
        Next();
        break;
        case Lexicon::STRING:
        Next();
        break;
        default:
        ReportMismatch();
    }
}

void Parser::ParseExpr()
{
    ParseAssignmentExpr();
}

void Parser::ParseAssignmentExpr()
{
    while(LexemeIs(Lexicon::ASSIGN) ||
        LexemeIs(Lexicon::ADD_ASSIGN)||
        LexemeIs(Lexicon::SUB_ASSIGN)||
        LexemeIs(Lexicon::MUL_ASSIGN)||
        LexemeIs(Lexicon::DIV_ASSIGN))
        {
            Next();
            // TO DO Handle recursion
        }

    ParseLogicalOrExpr();
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
    ParseAdditiveExpr();
    while(LexemeIs(Lexicon::EQUAL) || LexemeIs(Lexicon::NEQUAL))
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
    while(LexemeIs(Lexicon::ADD) || 
    LexemeIs(Lexicon::SUB) || 
    LexemeIs(Lexicon::NOT))
    {
        if(LexemeIs(Lexicon::ADD))
        {
            Next();
            if(LexemeIs(Lexicon::ADD))
            {
                // It is "++"
                Next();
            }
            else
            {
                // It is "+"
            }
        }
        else if(LexemeIs(Lexicon::SUB))
        {
            Next();
            if(LexemeIs(Lexicon::SUB))
            {
                // It is "--"
                Next();
            }
            else
            {
                // It is "-"
            }
        }
        else
        {
            // It is "!"
            Next();
        }


    }

    ParsePrimaryExpr();
}

void Parser::ParsePrimaryExpr()
{
    if(LexemeIs(Lexicon::IDENTIFIER) || 
    LexemeIs(Lexicon::REALVAL)       || 
    LexemeIs(Lexicon::BOOLVAL)       ||
    LexemeIs(Lexicon::STRINGVAL)     ||
    LexemeIs(Lexicon::INTVAL)        ||
    LexemeIs(Lexicon::OPAREN))
    {
        // Handle "( expr )"
        if(LexemeIs(Lexicon::OPAREN))
        {
            Next();
            ParseExpr();
            Match(Lexicon::CPAREN);
        }
        else
        {
            Next();
        }

    }
    else
    {
        ReportMismatch();
    }
}

void Parser::ParseStmt()
{
    // TODO: Calculate first sets
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
    // TODO: Parse Loop-Until after checking for first(stmt)

    Match(Lexicon::OPAREN);
    // TODO: Parse expr or var_decl by checking the first set
    Match(Lexicon::CPAREN);

    ParseStmt();
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

    // TODO: handle contents inside the compound stmt

    Match(Lexicon::CCURLY);
}