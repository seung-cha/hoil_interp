#ifndef LEX_ELIF_H
#define LEX_ELIF_H

#include "../lexicon.h"

namespace Lexicons
{
    class Elif : public Lexicon
    {
        public:
        Elif(int lineNo, int charNo) : Lexicon{Lexicon::ELIF, "elif", lineNo, charNo}
        {

        }

        std::string const ToString() const override
        {
            return "< ELIF, KWD >";
        }
    };

}

#endif