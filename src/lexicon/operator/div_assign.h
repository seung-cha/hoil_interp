#ifndef LEX_DIV_ASSIGN_H
#define LEX_DIV_ASSIGN_H

#include "../lexicon.h"

namespace Lexicons
{
    class DivAssign : public Lexicon
    {
        public:
        DivAssign(int lineNo, int charNo) : Lexicon{Lexicon::DIV_ASSIGN, lineNo, charNo}
        {

        }

        std::string const ToString() const override
        {
            return "< DIV_ASSIGN, /= >";
        }

    };

}

#endif