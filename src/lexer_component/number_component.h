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
            if(!(isdigit(scanner->currentChar) || scanner->currentChar == '.'))
            {
                CHAIN_RETURN;
            }

            bool decFound = false;
            std::ostringstream ss;
            lineNo = scanner->lineNo;
            charNo = scanner->charNo;
            
            while(isdigit(scanner->currentChar) || (!decFound && scanner->currentChar == '.'))
            {
                if(scanner->currentChar == '.')
                {
                    decFound = true;
                }

                ss << scanner->currentChar;
                scanner->Next();
            }

            scanner->Trim();

            // Error checking
            if(ss.str() == ".")
            {
                return new Lexicons::Error(ss.str(), lineNo, charNo);
            }
            else if(decFound)
            {
                float value = std::stof(ss.str());
                return new Lexicons::RealValue(value, ss.str(), lineNo, charNo);
            }
            else
            {
                int32_t value = static_cast<int32_t>(std::stoi(ss.str()));
                return new Lexicons::IntValue(value, ss.str(), lineNo, charNo);
            }
        }

    };


}


#endif