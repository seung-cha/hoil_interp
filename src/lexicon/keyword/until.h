#ifndef LEX_UNTIL_H
#define LEX_UNTIL_H

#include "../lexicon.h"

namespace Lexicons
{
    class Until : public Lexicon
    {
        public:
        Until(int lineNo, int charNo) : Lexicon{Lexicon::UNTIL, lineNo, charNo}
        {

        }

        std::string const ToString() const override
        {
            return "< UNTIL, KWD >";
        }
    };

}

#endif