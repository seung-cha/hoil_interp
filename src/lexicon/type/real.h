#ifndef LEX_REAL_H
#define LEX_REAL_H

#include "../lexicon.h"

namespace Lexicons
{
    class Real : public Lexicon
    {
        public:
        Real(int lineNo, int charNo) : Lexicon{Lexicon::REAL, "real", lineNo, charNo}
        {

        }

        std::string const ToString() const override
        {
            return "< REAL, TYPE >";
        }
    };


}

#endif