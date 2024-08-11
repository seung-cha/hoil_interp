#ifndef LEX_CONTINUE_H
#define LEX_CONTINUE_H

#include "../lexicon.h"

namespace Lexicons
{
    class Continue : public Lexicon
    {
        public:
        Continue(int lineNo, int charNo) : Lexicon{Lexicon::CONTINUE, lineNo, charNo}
        {

        }

        std::string const ToString() const override
        {
            return "< CONTINUE, KWD >";
        }
    };

}

#endif