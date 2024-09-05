/**
 *  THIS LEXEME IS NOT USED
 */
#ifndef LEX_FALSE_H
#define LEX_FALSE_H

#include "../lexicon.h"

namespace Lexicons
{
    class False : public Lexicon
    {
        public:
        False(int lineNo, int charNo) : Lexicon{Lexicon::FALSE, lineNo, charNo}
        {

        }

        std::string const ToString() const override
        {
            return "< FALSE, KWD >";
        }
    };

}

#endif