#ifndef LEX_SUBTRACT_H
#define LEX_SUBTRACT_H

#include "lexicon.h"

namespace Lexicons
{
    class Subtract : public Lexicon
    {
        public:
        Subtract(int lineNo, int charNo) : Lexicon{Lexicon::SUB, lineNo, charNo}
        {
            
        }

        std::string const ToString() const override
        {
            return "< SUB, - >";
        }

    };
}


#endif