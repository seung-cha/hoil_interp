#ifndef LEX_STRING_VAL_H
#define LEX_STRING_VAL_H

#include "../lexicon.h"

namespace Lexicons
{
    class StringValue : public Lexicon
    {
        public:
        std::string const value;
        StringValue(std::string const value, int lineNo, int charNo) : Lexicon{Lexicon::STRINGVAL, lineNo, charNo}, value{value}
        {

        }

        std::string const ToString() const override
        {
            char str[1024 + value.size()];
            snprintf(str, 1024 + sizeof(value), "< STRING_VALUE, %s >", value.c_str());
            return str;
        }

    };

}

#endif