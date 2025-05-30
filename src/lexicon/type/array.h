#ifndef LEX_ARRAY_H
#define LEX_ARRAY_H

#include "../lexicon.h"

namespace Lexicons
{
    class Array : public Lexicon
    {
        public:

        Array(int lineNo, int charNo) : Lexicon{Lexicon::ARRAY, "array", lineNo, charNo}
        {

        }

        std::string const ToString() const override
        {
            return "< ARRAY, TYPE >";
        }

    };


}

#endif