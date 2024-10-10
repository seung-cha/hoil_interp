#ifndef LEX_CLOSE_PAREN_H
#define LEX_CLOSE_PAREN_H

#include "../lexicon.h"

namespace Lexicons
{
    class CloseParen : public Lexicon
    {
        public:
        CloseParen(int lineNo, int charNo) : Lexicon{Lexicon::CPAREN, ")", lineNo, charNo}
        {

        }

        std::string const ToString() const override
        {
            return "< CPAREN, ) >";
        }
    };

}


#endif