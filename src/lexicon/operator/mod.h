#ifndef LEX_MOD_H
#define LEX_MOD_H

#include "../lexicon.h"

namespace Lexicons
{
    class Mod : public Lexicon
    {
        public:
        Mod(int lineNo, int charNo) : Lexicon{Lexicon::MOD, lineNo, charNo}
        {

        }

        std::string const ToString() const override
        {
            return "< MOD, % >";
        }
    };

}

#endif 