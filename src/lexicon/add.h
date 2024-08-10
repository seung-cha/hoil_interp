#ifndef LEX_ADD_H
#define LEX_ADD_H

#include "lexicon.h"

namespace Lexicons
{
    class Add : public Lexicon
    {
        public:
        Add(int lineNo, int charNo) : Lexicon(Lexicon::ADD, lineNo, charNo)
        {

        }

        std::string const ToString() const override
        {
            return "< ADD, + >";
        }
    };

}


#endif