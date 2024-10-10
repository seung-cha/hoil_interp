#ifndef LEX_CLOSE_SPAREN_H
#define LEX_CLOSE_SPAREN_H

#include "../lexicon.h"

namespace Lexicons
{
    class CloseSquareParen : public Lexicon
    {
        public:
        CloseSquareParen(int lineNo, int charNo) : Lexicon{Lexicon::CSPAREN, "]", lineNo, charNo}
        {

        }

        std::string const ToString() const override
        {
            return "< CSPAREN, ] >";
        }
    };

}


#endif