#ifndef LEXER_COMP_MISC_H
#define LEXER_COMP_MISC_H

#include "lexer_component.h"
#include "string_component.h"

namespace LexerComponents
{
    /**
     * Handle arithmetic operators
     */
    class MiscComponent : public LexerComponent
    {
        public:
        Lexicons::Lexicon *GetLexicon(Scanner *scanner) override
        {
            charNo = scanner->charNo;
            lineNo = scanner->lineNo;

            char c = scanner->currentChar;

            if(c == '_')
            {
                // Handle identifier

                std::ostringstream ss;
                while(isalnum(scanner->currentChar) || scanner->currentChar == '_')
                {   
                    ss << scanner->currentChar;
                    scanner->Next();
                }
                
                scanner->Trim();
                return new Lexicons::Identifier(ss.str(), lineNo, charNo);                
            }

          
            Lexicons::Lexicon *lex = nullptr;

            switch(c)
            {
                case '+':
                if(scanner->Peek() == '=')
                {
                    scanner->Next();
                    lex = new Lexicons::AddAssign(lineNo, charNo);
                }
                else if(scanner->Peek() == '+')
                {
                    scanner->Next();
                    lex = new Lexicons::UnaryAdd(lineNo, charNo);
                }
                else
                {
                    lex = new Lexicons::Add(lineNo, charNo);
                }
                break;
                case '-':
                if(scanner->Peek() == '=')
                {
                    scanner->Next();
                    lex = new Lexicons::SubAssign(lineNo, charNo);
                }
                else if(scanner->Peek() == '-')
                {
                    scanner->Next();
                    lex = new Lexicons::UnarySub(lineNo, charNo);
                }
                else if(scanner->Peek() == '>')
                {
                    scanner->Next();
                    lex = new Lexicons::RightArrow(lineNo, charNo);              
                }
                else
                {
                    lex = new Lexicons::Sub(lineNo, charNo);
                }
                break;
                case '*':
                if(scanner->Peek() == '=')
                {
                    scanner->Next();
                    lex = new Lexicons::MulAssign(lineNo, charNo);
                }
                else
                {
                    lex = new Lexicons::Mul(lineNo, charNo);
                }
                break;
                case '/':
                if(scanner->Peek() == '=')
                {
                    scanner->Next();
                    lex = new Lexicons::DivAssign(lineNo, charNo);
                }
                else
                {
                    lex = new Lexicons::Div(lineNo, charNo);
                }
                break;
                case '%':
                lex = new Lexicons::Mod(lineNo, charNo);
                break;
                case '=':
                if(scanner->Peek() == '=')
                {
                    scanner->Next();
                    lex = new Lexicons::Equal(lineNo, charNo);
                }
                else
                {
                    lex = new Lexicons::Assign(lineNo, charNo);
                }
                break;
                case '<':
                if(scanner->Peek() == '=')
                {
                    scanner->Next();
                    lex = new Lexicons::Lequal(lineNo, charNo);
                }
                else
                {
                    lex = new Lexicons::Less(lineNo, charNo);
                }
                break;
                case '>':
                if(scanner->Peek() == '=')
                {
                    scanner->Next();
                    lex = new Lexicons::Gequal(lineNo, charNo);
                }
                else if(scanner->Peek() == '>')
                {
                    //>> indicates instruct stmt
                    scanner->Next();
                    scanner->Next(); // Skip the two >
                    scanner->Trim(); // Trim any blank spaces inbetween

                    //
                    StringComponent strComp;
                    
                    Lexicons::Lexicon *strLex = strComp.GetLexicon(scanner);
                    if(strLex == nullptr)
                    {
                        lex = new Lexicons::Error(std::string{c}, lineNo, charNo);
                    }
                    else if(strLex->Id == Lexicons::Lexicon::ERR)
                    {
                        lex = strLex; // Error component
                    }
                    else
                    {
                        Lexicons::StringValue *v = static_cast<Lexicons::StringValue*>(strLex);
                        printf("value: %s\n", v->value.c_str());
                        lex = new Lexicons::Instruct{v->value, v->LineNo, v->CharNo};
                        delete strLex;
                    }
                }
                else
                {
                    lex = new Lexicons::Greater(lineNo, charNo);
                }
                break;
                case '!':
                if(scanner->Peek() == '=')
                {
                    scanner->Next();
                    lex = new Lexicons::Nequal(lineNo, charNo);
                }
                else
                {
                    lex = new Lexicons::Not(lineNo, charNo);
                }
                break;
                case '|':
                if(scanner->Peek() == '|')
                {
                    scanner->Next();
                    lex = new Lexicons::LogicalOr(lineNo, charNo);
                }
                else
                {
                    goto error_lex;
                }
                break;
                case '&':
                if(scanner->Peek() == '&')
                {
                    scanner->Next();
                    lex = new Lexicons::LogicalAnd(lineNo, charNo);
                }
                else
                {
                    goto error_lex;
                }
                break;
                case '(':
                lex = new Lexicons::OpenParen(lineNo, charNo);
                break;
                case ')':
                lex = new Lexicons::CloseParen(lineNo, charNo);
                break;
                case '[':
                lex = new Lexicons::OpenSquareParen(lineNo, charNo);
                break;
                case ']':
                lex = new Lexicons::CloseSquareParen(lineNo, charNo);
                break;
                case '{':
                lex = new Lexicons::OpenCurly(lineNo, charNo);
                break;
                case '}':
                lex = new Lexicons::CloseCurly(lineNo, charNo);
                break;
                case ';':
                lex = new Lexicons::Semicolon(lineNo, charNo);
                break;
                case ':':
                lex = new Lexicons::Colon(lineNo, charNo);
                break;
                case EOF:
                lex = new Lexicons::EndOfFile(lineNo, charNo);
                break;
                case ',':
                lex = new Lexicons::Comma(lineNo, charNo);
                break;
                case '\n':
                lex = new Lexicons::Newline(lineNo, charNo);
                break;
                default:
                error_lex:
                lex = new Lexicons::Error(std::string{c}, lineNo, charNo);
                break;
            }

            scanner->Seek();
            return lex;

        }

    };

}

#endif
