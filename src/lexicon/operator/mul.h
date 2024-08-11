#ifndef LEX_MUL_H
#define LEX_MUL_H

#include "../lexicon.h"

namespace Lexicons
{
    class Mul : public Lexicon
    {
        public:
        Mul(int lineNo, int charNo) : Lexicon{Lexicon::MUL, lineNo, charNo}
        {

        }

        std::string const ToString() const override
        {
            return "< MUL, * >";
        }
    };

}

#endif 