#ifndef LEX_NOT_H
#define LEX_NOT_H

#include "../lexicon.h"

namespace Lexicons
{
    class Not : public Lexicon
    {
        public:
        Not(int lineNo, int charNo) : Lexicon{Lexicon::NOT, lineNo, charNo}
        {

        }

        std::string const ToString() const override
        {
            return "< NOT, ! >";
        }

    };

}

#endif