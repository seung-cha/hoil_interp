#ifndef LEX_REAL_H
#define LEX_REAL_H

#include "../lexicon.h"

namespace Lexicons
{
    class Real : public Lexicon
    {
        public:
        float const value;

        Real(float const value, int lineNo, int charNo) : Lexicon{Lexicon::REAL, lineNo, charNo}, value{value}
        {

        }

        std::string const ToString() const override
        {
            char str[100];
            snprintf(str, 100, "< REAL, %f >", value);
            return str;
        }
    };


}

#endif