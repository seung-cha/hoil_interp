#ifndef LEX_LESS_H
#define LEX_LESS_H

#include "../lexicon.h"

namespace Lexicons
{
    class Less : public Lexicon
    {
        public:
        Less(int lineNo, int charNo) : Lexicon{Lexicon::LESS, "<", lineNo, charNo}
        {

        }

        std::string const ToString() const override
        {
            return "< LESS, < >";
        }

    };

}

#endif