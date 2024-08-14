#ifndef LEX_REAL_VALUE_H
#define LEX_REAL_VALUE_H

#include "../lexicon.h"

namespace Lexicons
{
    class RealValue : public Lexicon
    {
        public:
        float const value;

        RealValue(float const value, int lineNo, int charNo) : Lexicon{Lexicon::REALVAL, lineNo, charNo}, value{value}
        {

        }

        std::string const ToString() const override
        {
            char str[1024];
            snprintf(str, 1024, "< REAL_VALUE, %f >", value);
            return str;
        }
    };


}

#endif