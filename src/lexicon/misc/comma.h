#ifndef LEX_COMMA_H
#define LEX_COMMA_H

#include "../lexicon.h"

namespace Lexicons
{
    class Comma : public Lexicon
    {
        public:
        Comma(int lineNo, int charNo) : Lexicon{Lexicon::COMMA, ",", lineNo, charNo}
        {

        }

        std::string const ToString() const override
        {
            return "< COMMA, , >";
        }
    };

}


#endif