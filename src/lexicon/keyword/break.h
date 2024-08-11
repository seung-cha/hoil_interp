#ifndef LEX_BREAK_H
#define LEX_BREAK_H

#include "../lexicon.h"

namespace Lexicons
{
    class Break : public Lexicon
    {
        public:
        Break(int lineNo, int charNo) : Lexicon{Lexicon::BREAK, lineNo, charNo}
        {

        }

        std::string const ToString() const override
        {
            return "< BREAK, KWD >";
        }
    };

}

#endif