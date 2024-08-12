#ifndef LEX_NEQUAL_H
#define LEX_NEQUAL_H

#include "../lexicon.h"

namespace Lexicons
{
    class Nequal : public Lexicon
    {
        public:
        Nequal(int lineNo, int charNo) : Lexicon{Lexicon::NEQUAL, lineNo, charNo}
        {

        }

        std::string const ToString() const override
        {
            return "< NEQUAL, != >";
        }

    };

}

#endif