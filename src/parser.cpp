#include <sstream>
#include "lexer.h"
#include "parser.h"

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
        ss << "Unexpected Token: " << currentLexicon->Verbose() << std::endl;
        errorMsgs.push_back(ss.str());
    }

    Next();
}

void Parser::Analyse()
{
    
}