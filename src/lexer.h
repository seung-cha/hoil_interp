#ifndef LEXER_H
#define LEXER_H

#include <string>
#include <vector>
#include "scanner.h"
#include "lexemes.h"
#include "lexer_components.h"

class Lexer
{
    public:
    Lexer(Scanner *scanner);
    ~Lexer();

    /**
     * Get the next lexicon. Return nullptr if nothing is available.
     */
    Lexicons::Lexicon *GetLexicon();

    /**
     * Return stats in form:
     * Tokens: N
     * Errors: E
     */
    void Verbose();

    private:
    int ctr = 0;
    std::vector<Lexicons::Lexicon*> lexemes;
    Scanner *scanner;
    LexerComponents::LexerComponent *componentHead;

    LexerComponents::NumberComponent numComp;
    LexerComponents::MiscComponent miscComp;
    LexerComponents::StringComponent strComp;
    LexerComponents::AlphabetComponent alphaComp;

};

#endif