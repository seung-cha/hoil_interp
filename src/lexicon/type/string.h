#ifndef LEX_STRING_H
#define LEX_STRING_H

#include "../lexicon.h"

namespace Lexicons
{
    class String : public Lexicon
    {
        public:
        String(int lineNo, int charNo) : Lexicon{Lexicon::STRING, lineNo, charNo}
        {

        }

        std::string const ToString() const override
        {
            return "< STRING, TYPE >";
        }

    };

}

#endif