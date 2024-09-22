#ifndef LEX_LOOP_H
#define LEX_LOOP_H

#include "../lexicon.h"

namespace Lexicons
{
    class Loop : public Lexicon
    {
        public:
        Loop(int lineNo, int charNo) : Lexicon{Lexicon::LOOP, lineNo, charNo}
        {

        }

        std::string const ToString() const override
        {
            return "< LOOP, KWD >";
        }
    };

}

#endif