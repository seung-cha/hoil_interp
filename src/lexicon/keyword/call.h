#ifndef LEX_CALL_H
#define LEX_CALL_H

#include "../lexicon.h"

namespace Lexicons
{
    class Call : public Lexicon
    {
        public:
        Call(int lineNo, int charNo) : Lexicon{Lexicon::CALL, "call", lineNo, charNo}
        {

        }

        std::string const ToString() const override
        {
            return "< CALL, KWD >";
        }
    };

}

#endif