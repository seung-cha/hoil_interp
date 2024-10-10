#ifndef LEX_ADD_ASSIGN_H
#define LEX_ADD_ASSIGN_H

#include "../lexicon.h"

namespace Lexicons
{
    class AddAssign : public Lexicon
    {
        public:
        AddAssign(int lineNo, int charNo) : Lexicon{Lexicon::ADD_ASSIGN, "+=", lineNo, charNo}
        {

        }

        std::string const ToString() const override
        {
            return "< ADD_ASSIGN, += >";
        }

    };

}

#endif