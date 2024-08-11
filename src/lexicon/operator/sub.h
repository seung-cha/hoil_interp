#ifndef LEX_SUB_H
#define LEX_SUB_H

#include "../lexicon.h"

namespace Lexicons
{
    class Sub : public Lexicon
    {
        public:
        Sub(int lineNo, int charNo) : Lexicon{Lexicon::SUB, lineNo, charNo}
        {
            
        }

        std::string const ToString() const override
        {
            return "< SUB, - >";
        }

    };
}


#endif