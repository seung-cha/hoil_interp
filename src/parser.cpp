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
        currentLexicon->Id == Lexicon::INT  ||
        currentLexicon->Id == Lexicon::REAL ||
        currentLexicon->Id == Lexicon::BOOL ||
        currentLexicon->Id == Lexicon::STRING ||
        currentLexicon->Id == Lexicon::VOID
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

    // TODO
    if(currentLexicon->Id == Lexicon::ASSIGN)
    {
        
    }
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

