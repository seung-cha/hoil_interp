#ifndef LEX_IF_H
#define LEX_IF_H

#include "../lexicon.h"

namespace Lexicons
{
    class If : public Lexicon
    {
        public:
        If(int lineNo, int charNo) : Lexicon{Lexicon::IF, lineNo, charNo}
        {

        }

        std::string const ToString() const override
        {
            return "< IF, KWD >";
        }
    };

}

#endif