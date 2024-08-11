#ifndef LEXER_COMP_OPERATOR_H
#define LEXER_COMP_OPERATOR_H

#include "lexer_component.h"

namespace LexerComponents
{
    /**
     * Handle arithmetic operators
     */
    class OperatorComponent : public LexerComponent
    {
        public:
        Lexicons::Lexicon *GetLexicon(Scanner* scanner) override
        {
            char c = scanner->currentChar;
            if(c != '*' && c != '/' && c != '-' && c != '+')
            {
                CHAIN_RETURN;
            }

            charNo = scanner->charNo;
            lineNo = scanner->lineNo;
            Lexicons::Lexicon *lex;

            switch(c)
            {
                case '+':
                lex = new Lexicons::Add(lineNo, charNo);
                break;
                case '-':
                lex = new Lexicons::Sub(lineNo, charNo);
                break;
                case '*':
                lex = new Lexicons::Mul(lineNo, charNo);
                break;
                case '/':
                lex = new Lexicons::Div(lineNo, charNo);
                break;
            }

            scanner->Seek();
            return lex;

        }

    };

}

#endif
