#ifndef LEX_FOR_H
#define LEX_FOR_H

#include "../lexicon.h"

namespace Lexicons
{
    class For : public Lexicon
    {
        public:
        For(int lineNo, int charNo) : Lexicon{Lexicon::FOR, lineNo, charNo}
        {

        }

        std::string const ToString() const override
        {
            return "< FOR, KWD >";
        }
    };

}

#endif