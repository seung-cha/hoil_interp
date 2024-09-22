#ifndef LEX_RETURN_H
#define LEX_RETURN_H

#include "../lexicon.h"

namespace Lexicons
{
    class Return : public Lexicon
    {
        public:
        Return(int lineNo, int charNo) : Lexicon{Lexicon::RETURN, lineNo, charNo}
        {

        }

        std::string const ToString() const override
        {
            return "< RETURN, KWD >";
        }
    };

}

#endif