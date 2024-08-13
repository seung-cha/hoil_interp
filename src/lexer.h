#ifndef LEXER_H
#define LEXER_H

#include <string>
#include "scanner.h"
#include "lexemes.h"
#include "lexer_components.h"

class Lexer
{
    public:
    Lexer(Scanner *scanner);

    /**
     * Get the next lexicon. Return nullptr if nothing is available.
     */
    Lexicons::Lexicon *GetLexicon();

    private:
    Scanner *scanner;
    LexerComponents::LexerComponent *componentHead;

    LexerComponents::NumberComponent numComp;
    LexerComponents::MiscComponent miscComp;
    LexerComponents::StringComponent strComp;
    LexerComponents::AlphabetComponent alphaComp;

};

#endif