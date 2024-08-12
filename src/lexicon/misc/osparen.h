#ifndef LEX_OPEN_SPAREN_H
#define LEX_OPEN_SPAREN_H

#include "../lexicon.h"

namespace Lexicons
{
    class OpenSquareParen : public Lexicon
    {
        public:
        OpenSquareParen(int lineNo, int charNo) : Lexicon{Lexicon::OSPAREN, lineNo, charNo}
        {

        }

        std::string const ToString() const override
        {
            return "< OSPAREN, [ >";
        }
    };

}


#endif