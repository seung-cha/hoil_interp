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
                lex = new Lexicons::BoolValue(true, str, lineNo, charNo);
            }
            else if(str == "false")
            {
                lex = new Lexicons::BoolValue(false, str, lineNo, charNo);
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
            // else if(str == "int")
            // {
            //     lex = new Lexicons::Int(lineNo, charNo);
            // }
            else if(str == "Number")
            {
                lex = new Lexicons::Real(lineNo, charNo);
            }
            else if(str == "Logic")
            {
                lex = new Lexicons::Bool(lineNo, charNo);
            }
            else if(str == "Sentence")
            {
                lex = new Lexicons::String(lineNo, charNo);
            }
            else if(str == "void")
            {
                lex = new Lexicons::Void(lineNo, charNo);
            }
            else if(str == "return")
            {
                lex = new Lexicons::Return(lineNo, charNo);
            }
            else if(str == "repeat")
            {
                lex = new Lexicons::Loop(lineNo, charNo);
            }
            else if(str == "until")
            {
                lex = new Lexicons::Until(lineNo, charNo);
            }
            else if(str == "Object")
            {
                lex = new Lexicons::Object(lineNo, charNo);
            }
            else if(str == "Attribute")
            {
                lex = new Lexicons::Attribute(lineNo, charNo);
            }
            else if(str == "is")
            {
                lex = new Lexicons::Is(lineNo, charNo);
            }
            else if(str == "not")
            {
                lex = new Lexicons::NotKwd(lineNo,  charNo);
            }
            else if(str == "equals")
            {
                lex = new Lexicons::EqualKwd(lineNo, charNo);
            }
            else if(str == "and")
            {
                lex = new Lexicons::LogicalAnd(lineNo, charNo);
            }
            else if(str == "or")
            {
                lex = new Lexicons::LogicalOr(lineNo, charNo);
            }
            else if(str == "define")
            {
                lex = new Lexicons::Define(lineNo, charNo);
            }
            else
            {
                while(isalnum(scanner->currentChar))
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