#ifndef LEXER_COMP_ALPHABET_H
#define LEXER_COMP_ALPHABET_H

#include "lexer_component.h"

namespace LexerComponents
{
    /**
     * Handle all lexers starting with an alphabet (i.e keywords, identifier)
     */
    class AlphabetComponent : public LexerComponent
    {

        public:
        Lexicons::Lexicon *GetLexicon(Scanner *scanner) override
        {
            lineNo = scanner->lineNo;
            charNo = scanner->charNo;
            Lexicons::Lexicon *lex = nullptr;

            if(!isalpha(scanner->currentChar))
            {
                CHAIN_RETURN;
            }

            std::ostringstream ss;
            while(isalpha(scanner->currentChar))
            {   
                ss << scanner->currentChar;
                scanner->Next();
            }
            std::string const str = ss.str();
            if(str == "true")
            {
                lex = new Lexicons::True(lineNo, charNo);
            }
            else if(str == "false")
            {
                lex = new Lexicons::False(lineNo, charNo);
            }
            else if(str == "if")
            {
                lex = new Lexicons::If(lineNo, charNo);
            }
            else if(str == "elif")
            {
                lex = new Lexicons::Elif(lineNo, charNo);
            }
            else if(str == "else")
            {
                lex = new Lexicons::Else(lineNo, charNo);
            }
            else if(str == "for")
            {
                lex = new Lexicons::For(lineNo, charNo);
            }
            else if(str == "while")
            {
                lex = new Lexicons::While(lineNo, charNo);
            }
            else if(str == "do")
            {
                lex = new Lexicons::Do(lineNo, charNo);
            }
            else if(str == "break")
            {
                lex = new Lexicons::Break(lineNo, charNo);
            }
            else if(str == "continue")
            {
                lex = new Lexicons::Continue(lineNo, charNo);
            }
            else
            {
                while(isalnum(scanner->currentChar) || scanner->currentChar == '_')
                {   
                    ss << scanner->currentChar;
                    scanner->Next();
                }

                lex = new Lexicons::Identifier(ss.str(), lineNo, charNo);
            }

            scanner->Trim();
            return lex;
        }
    };
}

#endif