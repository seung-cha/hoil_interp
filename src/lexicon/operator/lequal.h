#ifndef LEX_LEQUAL_H
#define LEX_LEQUAL_H

#include "../lexicon.h"

namespace Lexicons
{
    class Lequal : public Lexicon
    {
        public:
        Lequal(int lineNo, int charNo) : Lexicon{Lexicon::LEQUAL, "<=", lineNo, charNo}
        {

        }

        std::string const ToString() const override
        {
            return "< LEQUAL, <= >";
        }

    };

}

#endif