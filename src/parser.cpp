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
    // As of now, handle single var declaration only.
    ParseType();
    Match(Lexicon::IDENTIFIER);
    Match(Lexicon::SEMICOLON);
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

