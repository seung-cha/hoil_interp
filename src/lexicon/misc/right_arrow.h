#ifndef LEX_RIGHT_ARR_H
#define LEX_RIGHT_ARR_H

#include "../lexicon.h"

namespace Lexicons
{
    class RightArrow : public Lexicon
    {
        public:
        RightArrow(int lineNo, int charNo) : Lexicon{Lexicon::RIGHT_ARR, "->", lineNo, charNo}
        {

        }

        std::string const ToString() const override
        {
            return "< RIGHT_ARROW, -> >";
        }
    };

}


#endif