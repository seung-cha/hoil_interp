#ifndef LEX_ELSE_H
#define LEX_ELSE_H

#include "../lexicon.h"

namespace Lexicons
{
    class Else : public Lexicon
    {
        public:
        Else(int lineNo, int charNo) : Lexicon{Lexicon::ELSE, "else", lineNo, charNo}
        {

        }

        std::string const ToString() const override
        {
            return "< ELSE, KWD >";
        }
    };

}

#endif