#ifndef LEX_MUL_ASSIGN_H
#define LEX_MUL_ASSIGN_H

#include "../lexicon.h"

namespace Lexicons
{
    class MulAssign : public Lexicon
    {
        public:
        MulAssign(int lineNo, int charNo) : Lexicon{Lexicon::MUL_ASSIGN, "*=", lineNo, charNo}
        {

        }

        std::string const ToString() const override
        {
            return "< MUL_ASSIGN, *= >";
        }

    };

}

#endif