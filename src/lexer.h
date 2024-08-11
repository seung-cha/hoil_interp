#ifndef LEXER_H
#define LEXER_H

#include <string>
#include "scanner.h"
#include "lexicons.h"
#include "lexer_components.h"

class Lexer
{
    public:
    Lexer(Scanner *scanner);

    Lexicons::Lexicon *GetLexicon();

    private:
    Scanner *scanner;
    LexerComponents::LexerComponent *componentHead;

    LexerComponents::NumberComponent numComp;
    LexerComponents::OperatorComponent opComp;
    LexerComponents::StringComponent strComp;

};

#endif