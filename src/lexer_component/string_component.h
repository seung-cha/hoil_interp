#ifndef LEXER_COMP_STRING_H
#define LEXER_COMP_STRING_H

#include "lexer_component.h"
#include <sstream>
#include <cassert>
namespace LexerComponents
{
    class StringComponent : public LexerComponent
    {
        public:
        Lexicons::Lexicon *GetLexicon(Scanner *scanner) override
        {
            if(scanner->currentChar != '\"')
            {
                CHAIN_RETURN;
            }

            lineNo = scanner->lineNo;
            charNo = scanner->charNo;

            std::ostringstream ss; 
            scanner->Next();
            while(scanner->currentChar != '\"')
            {
                ss << scanner->currentChar;
                if(scanner->Next() == EOF)
                {
                    // TODO: handle string-not-terminated error
                    return new Lexicons::Error(ss.str(), lineNo, charNo);
                }
            }
            scanner->Seek();
            return new Lexicons::StringValue(ss.str(), lineNo, charNo);
        }
    };

}


#endif