#ifndef LEX_NOT_KWD_H
#define LEX_NOT_KWD_H

#include "../lexicon.h"

namespace Lexicons
{
    class NotKwd : public Lexicon
    {
        public:
        NotKwd(int lineNo, int charNo) : Lexicon{Lexicon::NOT_KWD, "not", lineNo, charNo}
        {

        }

        std::string const ToString() const override
        {
            return "< NOT, KWD >";
        }
    };

}

#endif