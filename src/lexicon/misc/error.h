#ifndef LEX_ERR_H
#define LEX_ERR_H

#include "../lexicon.h"

namespace Lexicons
{
    class Error : public Lexicon
    {
        public:
        char value;
        Error(char value, int lineNo, int charNo) : Lexicon{Lexicon::ERR, lineNo, charNo}, value{value}
        {

        }

        std::string const ToString() const override
        {
            char str[100];
            snprintf(str, 100, "< ERROR, %c >", value);
            return str;
        }
    };

}


#endif