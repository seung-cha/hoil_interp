#ifndef LEX_GREATER_H
#define LEX_GREATER_H

#include "../lexicon.h"

namespace Lexicons
{
    class Greater : public Lexicon
    {
        public:
        Greater(int lineNo, int charNo) : Lexicon{Lexicon::GREATER, lineNo, charNo}
        {

        }

        std::string const ToString() const override
        {
            return "< Greater, > >";
        }

    };

}

#endif