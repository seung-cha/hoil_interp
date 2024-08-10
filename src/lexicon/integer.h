#ifndef LEX_INTEGER_H
#define LEX_INTEGER_H

#include "lexicon.h"

namespace Lexicons
{
    class Integer : public Lexicon
    {
        public:
        int const value;

        Integer(int value, int lineNo, int charNo) : Lexicon{Lexicon::INT, lineNo, charNo}, value{value}
        {

        }

        std::string const ToString() const override
        {
            char str[100];
            snprintf(str, 100, "< ADD, %d >", value);
            return str;
        }

    };


}

#endif