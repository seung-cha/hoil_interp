#ifndef LEX_ID_H
#define LEX_ID_H

#include "../lexicon.h"

namespace Lexicons
{
    class Identifier : public Lexicon
    {
        public:
        Identifier(std::string spelling, int lineNo, int charNo) : Lexicon{Lexicon::IDENTIFIER, spelling, lineNo, charNo}
        {

        }

        std::string const ToString() const override
        {
            char str[1024 + spelling.size()];
            snprintf(str, 1024 + sizeof(spelling), "< IDENTIFIER, %s >", spelling.c_str());
            return str;
        }
    };

}


#endif