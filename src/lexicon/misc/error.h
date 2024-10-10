#ifndef LEX_ERR_H
#define LEX_ERR_H

#include "../lexicon.h"

namespace Lexicons
{
    class Error : public Lexicon
    {
        public:

        Error(std::string spelling, int lineNo, int charNo) : Lexicon{Lexicon::ERR, spelling, lineNo, charNo}
        {

        }

        std::string const ToString() const override
        {
            char str[100 + spelling.size()];
            snprintf(str, 100, "< ERROR, %s >", spelling.c_str());
            return str;
        }
    };

}


#endif