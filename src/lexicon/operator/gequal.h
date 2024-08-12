#ifndef LEX_GEQUAL_H
#define LEX_GEQUAL_H

#include "../lexicon.h"

namespace Lexicons
{
    class Gequal : public Lexicon
    {
        public:
        Gequal(int lineNo, int charNo) : Lexicon{Lexicon::GEQUAL, lineNo, charNo}
        {

        }

        std::string const ToString() const override
        {
            return "< GEQUAL, >= >";
        }

    };

}

#endif