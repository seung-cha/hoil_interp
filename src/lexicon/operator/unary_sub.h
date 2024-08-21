#ifndef LEX_UNARY_SUB_H
#define LEX_UNARY_SUB_H

#include "../lexicon.h"

namespace Lexicons
{
    class UnarySub : public Lexicon
    {
        public:
        UnarySub(int lineNo, int charNo) : Lexicon{Lexicon::UNARY_SUB, lineNo, charNo}
        {

        }

        std::string const ToString() const override
        {
            return "< UNARY_SUB, -- >";
        }
    };

}


#endif