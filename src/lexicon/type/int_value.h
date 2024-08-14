#ifndef LEX_INT_VALUE_H
#define LEX_INT_VALUE_H

#include "../lexicon.h"

namespace Lexicons
{
    class IntValue : public Lexicon
    {
        public:
        int32_t const value;

        IntValue(int32_t const value, int lineNo, int charNo) : Lexicon{Lexicon::INTVAL, lineNo, charNo}, value{value}
        {

        }

        std::string const ToString() const override
        {
            char str[1024];
            snprintf(str, 1024, "< INT_VALUE, %d >", value);
            return str;
        }

    };


}

#endif