#ifndef LEX_EQUAL_H
#define LEX_EQUAL_H

#include "../lexicon.h"

namespace Lexicons
{
    class Equal : public Lexicon
    {
        public:
        Equal(int lineNo, int charNo) : Lexicon{Lexicon::EQUAL, "==", lineNo, charNo}
        {

        }

        std::string const ToString() const override
        {
            return "< EQUAL, == >";
        }

    };

}

#endif