#ifndef LEXER_H
#define LEXER_H

#include "scanner.h"
#include <string>
#include "lexicons.h"

class Lexer
{
    public:
    Lexer(Scanner& scanner) : scanner{&scanner}
    {

    }

    Lexicons::Lexicon *GetLexicon();

    private:
    Scanner *scanner;

};

#endif