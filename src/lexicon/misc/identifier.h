#ifndef LEX_ID_H
#define LEX_ID_H

#include "../lexicon.h"

namespace Lexicons
{
    class Identifier : public Lexicon
    {
        public:
        std::string const value;
        Identifier(std::string const value, int lineNo, int charNo) : Lexicon{Lexicon::ID, lineNo, charNo}, value{value}
        {

        }

        std::string const ToString() const override
        {
            char str[1024 + value.size()];
            snprintf(str, 1024 + sizeof(value), "< ID, %s >", value.c_str());
            return str;
        }
    };

}


#endif