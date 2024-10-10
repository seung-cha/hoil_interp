#ifndef LEX_UNARY_ADD_H
#define LEX_UNARY_ADD_H

#include "../lexicon.h"

namespace Lexicons
{
    class UnaryAdd : public Lexicon
    {
        public:
        UnaryAdd(int lineNo, int charNo) : Lexicon{Lexicon::UNARY_ADD, "++", lineNo, charNo}
        {

        }

        std::string const ToString() const override
        {
            return "< UNARY_ADD, ++ >";
        }
    };

}


#endif