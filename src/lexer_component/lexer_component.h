#ifndef LEXER_COMP_H
#define LEXER_COMP_H

#include <sstream>
#include "cctype"

#include "../scanner.h"
#include "../lexicons.h"

namespace LexerComponents
{
    /**
     * Return nullptr if next is null. Otherwise let the next chain handle input.
     */
    #define CHAIN_RETURN return next ? next->GetLexicon(scanner) : nullptr

    /**
     * Base class to handle lexicons using the CoR pattern.
     * A component delegates scanner to the next one if it cannot handle the current character.
     * If a component returns with a token, it calls scanner->Seek(), changing the current token.
     */
    class LexerComponent
    {
        public:
        LexerComponent *Chain(LexerComponent *next)
        {
            this->next = next;
            return next;
        }

        virtual Lexicons::Lexicon *GetLexicon(Scanner *scanner) = 0;

        protected:
        LexerComponent *next = nullptr;
        int charNo;
        int lineNo;
    };

}


#endif