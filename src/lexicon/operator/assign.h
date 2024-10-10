#ifndef LEX_ASSIGN_H
#define LEX_ASSIGN_H

#include "../lexicon.h"

namespace Lexicons
{
    class Assign : public Lexicon
    {
        public:
        Assign(int lineNo, int charNo) : Lexicon{Lexicon::ASSIGN, "=", lineNo, charNo}
        {

        }

        std::string const ToString() const override
        {
            return "< ASSIGN, = >";
        }

    };

}

#endif