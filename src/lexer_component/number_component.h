#ifndef LEXER_COMP_NUMBER_H
#define LEXER_COMP_NUMBER_H

#include <cassert>
#include "lexer_component.h"

namespace LexerComponents
{
    /**
     * Handle int or real
     */
    class NumberComponent : public LexerComponent
    {
        Lexicons::Lexicon *GetLexicon(Scanner *scanner) override
        {
            if(!isdigit(scanner->currentChar))
            {
                CHAIN_RETURN;
            }

            std::ostringstream ss;
            lineNo = scanner->lineNo;
            charNo = scanner->charNo;
            
            while(isdigit(scanner->currentChar))
            {
                ss << scanner->currentChar;
                scanner->Seek();
            }

            int32_t value = static_cast<int32_t>(std::stoi(ss.str()));
            //return new Lexicons::Int(value, lineNo, charNo);
            assert(false && "values unsupported as of now");
        }

    };


}


#endif