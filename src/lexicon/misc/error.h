#ifndef LEX_ERR_H
#define LEX_ERR_H

#include "../lexicon.h"

namespace Lexicons
{
    class Error : public Lexicon
    {
        public:
        std::string value;
        Error(std::string value, int lineNo, int charNo) : Lexicon{Lexicon::ERR, lineNo, charNo}, value{value}
        {

        }

        std::string const ToString() const override
        {
            char str[100 + value.size()];
            snprintf(str, 100, "< ERROR, %s >", value.c_str());
            return str;
        }
    };

}


#endif