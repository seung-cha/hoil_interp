#ifndef LEX_OPEN_PAREN_H
#define LEX_OPEN_PAREN_H

#include "../lexicon.h"

namespace Lexicons
{
    class OpenParen : public Lexicon
    {
        public:
        OpenParen(int lineNo, int charNo) : Lexicon{Lexicon::OPAREN, "(", lineNo, charNo}
        {

        }

        std::string const ToString() const override
        {
            return "< OPAREN, ( >";
        }
    };

}


#endif