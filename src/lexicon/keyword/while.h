#ifndef LEX_WHILE_H
#define LEX_WHILE_H

#include "../lexicon.h"

namespace Lexicons
{
    class While : public Lexicon
    {
        public:
        While(int lineNo, int charNo) : Lexicon{Lexicon::WHILE, lineNo, charNo}
        {

        }

        std::string const ToString() const override
        {
            return "< WHILE, KWD >";
        }
    };

}

#endif