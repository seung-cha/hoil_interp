#ifndef LEX_VOID_H
#define LEX_VOID_H

#include "../lexicon.h"

namespace Lexicons
{
    class Void : public Lexicon
    {
        public:

        Void(int lineNo, int charNo) : Lexicon{Lexicon::VOID, lineNo, charNo}
        {

        }

        std::string const ToString() const override
        {
            return "< VOID, TYPE >";
        }

    };


}

#endif