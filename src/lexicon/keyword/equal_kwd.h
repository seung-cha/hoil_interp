#ifndef LEX_EQUAL_KWD_H
#define LEX_EQUAL_KWD_H

#include "../lexicon.h"

namespace Lexicons
{
    class EqualKwd : public Lexicon
    {
        public:
        EqualKwd(int lineNo, int charNo) : Lexicon{Lexicon::EQUAL_KWD, "equals", lineNo, charNo}
        {

        }

        std::string const ToString() const override
        {
            return "< EQUALS, KWD >";
        }
    };

}

#endif