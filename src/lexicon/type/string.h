#ifndef LEX_STRING_H
#define LEX_STRING_H

#include "../lexicon.h"

namespace Lexicons
{
    class String : public Lexicon
    {
        public:
        std::string value;
        String(char* value, int lineNo, int charNo) : Lexicon{Lexicon::STRING, lineNo, charNo}, value{value}
        {

        }

        std::string const ToString() const override
        {
            char str[100 + value.size()];
            snprintf(str, 100 + sizeof(value), "< STRING, %s >", str);
            return str;
        }

    };

}

#endif