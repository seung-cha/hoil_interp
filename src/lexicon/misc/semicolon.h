#ifndef LEX_SEMICOLON_H
#define LEX_SEMICOLON_H

#include "../lexicon.h"

namespace Lexicons
{
    class Semicolon : public Lexicon
    {
        public:
        Semicolon(int lineNo, int charNo) : Lexicon{Lexicon::SEMICOLON, lineNo, charNo}
        {

        }

        std::string const ToString() const override
        {
            return "< SEMICOLON, ; >";
        }
    };

}


#endif