#ifndef LEX_DEFINE_H
#define LEX_DEFINE_H

#include "../lexicon.h"

namespace Lexicons
{
    class Define : public Lexicon
    {
        public:
        Define(int lineNo, int charNo) : Lexicon{Lexicon::DEFINE, "define", lineNo, charNo}
        {

        }

        std::string const ToString() const override
        {
            return "< DEFINE, KWD >";
        }
    };

}

#endif