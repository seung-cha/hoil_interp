#include <sstream>
#include "lexer.h"
#include "parser.h"

using namespace Lexicons;

Parser::Parser(Lexer *lexer) : lexer{lexer}
{
    Next();
}

void Parser::Next()
{
    currentLexicon = lexer->GetLexicon();
}

void Parser::Match(Lexicons::LexiconId id)
{
    if(currentLexicon->Id != id)
    {
        std::ostringstream ss;
        ss << "Unexpected Token: " << currentLexicon->Verbose();
        errorMsgs.push_back(ss.str());
    }

    Next();
}

void Parser::Analyse()
{
}