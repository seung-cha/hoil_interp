#ifndef LEX_DIV_H
#define LEX_DIV_H

#include "../lexicon.h"

namespace Lexicons
{
    class Div : public Lexicon
    {
        public:
        Div(int lineNo, int charNo) : Lexicon{Lexicon::DIV, "/", lineNo, charNo}
        {

        }

        std::string const ToString() const override
        {
            return "< DIV, / >";
        }

    };

}

#endif