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
            
            scanner->Trim();
            std::string const str = ss.str();
            if(str == "true")
            {
                return new Lexicons::True(lineNo, charNo);
            }
            else if(str == "false")
            {
                return new Lexicons::False(lineNo, charNo);
            }
            else if(str == "if")
            {
                return new Lexicons::If(lineNo, charNo);
            }
            else if(str == "elif")
            {
                return new Lexicons::Elif(lineNo, charNo);
            }
            else if(str == "else")
            {
                return new Lexicons::Else(lineNo, charNo);
            }
            else if(str == "for")
            {
                return new Lexicons::For(lineNo, charNo);
            }
            else if(str == "while")
            {
                return new Lexicons::While(lineNo, charNo);
            }
            else if(str == "do")
            {
                return new Lexicons::Do(lineNo, charNo);
            }
            else if(str == "break")
            {
                return new Lexicons::Break(lineNo, charNo);
            }
            else if(str == "continue")
            {
                return new Lexicons::Continue(lineNo, charNo);
            }
            else
            {
                // TODO: Handle identifier
                return new Lexicons::Identifier(ss.str(), lineNo, charNo);
            }


        }
    };
}

#endif