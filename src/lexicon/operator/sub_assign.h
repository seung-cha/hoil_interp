#ifndef LEX_SUB_ASSIGN_H
#define LEX_SUB_ASSIGN_H

#include "../lexicon.h"

namespace Lexicons
{
    class SubAssign : public Lexicon
    {
        public:
        SubAssign(int lineNo, int charNo) : Lexicon{Lexicon::SUB_ASSIGN, lineNo, charNo}
        {

        }

        std::string const ToString() const override
        {
            return "< SUB_ASSIGN, -= >";
        }

    };

}

#endif