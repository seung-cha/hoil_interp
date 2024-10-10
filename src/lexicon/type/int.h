#ifndef LEX_INT_H
#define LEX_INT_H

#include "../lexicon.h"

namespace Lexicons
{
    class Int : public Lexicon
    {
        public:

        Int(int lineNo, int charNo) : Lexicon{Lexicon::INT, "int", lineNo, charNo}
        {

        }

        std::string const ToString() const override
        {
            return "< INT, TYPE >";
        }

    };


}

#endif