#ifndef LEX_INSTRUCT_H
#define LEX_INSTRUCT_H

#include "../lexicon.h"

namespace Lexicons
{
    class Instruct : public Lexicon
    {
    public:
        std::string const value;

        Instruct(std::string const value, int lineNo, int charNo) : Lexicon{Lexicon::INSTRUCT, value, lineNo, charNo}, value{value}
        {
        }

        std::string const ToString() const override
        {
            char str[1024 + value.size()];
            snprintf(str, 1024 + sizeof(value), "< INSTRUCT_VALUE, %s >", value.c_str());
            return str;
        }
    };

}

#endif