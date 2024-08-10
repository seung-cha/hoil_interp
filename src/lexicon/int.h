#ifndef LEX_INT_H
#define LEX_INT_H

#include "lexicon.h"

namespace Lexicons
{
    class Int : public Lexicon
    {
        public:
        int32_t const value;

        Int(int32_t value, int lineNo, int charNo) : Lexicon{Lexicon::INT, lineNo, charNo}, value{value}
        {

        }

        std::string const ToString() const override
        {
            char str[100];
            snprintf(str, 100, "< INT, %d >", value);
            return str;
        }

    };


}

#endif