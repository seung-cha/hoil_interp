#ifndef LEX_COLON_H
#define LEX_COLON_H

#include "../lexicon.h"

namespace Lexicons
{
    class Colon : public Lexicon
    {
        public:
        Colon(int lineNo, int charNo) : Lexicon{Lexicon::COLON, ":", lineNo, charNo}
        {

        }

        std::string const ToString() const override
        {
            return "< COLON, : >";
        }
    };

}


#endif