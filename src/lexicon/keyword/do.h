#ifndef LEX_DO_H
#define LEX_DO_H

#include "../lexicon.h"

namespace Lexicons
{
    class Do : public Lexicon
    {
        public:
        Do(int lineNo, int charNo) : Lexicon{Lexicon::DO, lineNo, charNo}
        {

        }

        std::string const ToString() const override
        {
            return "< DO, KWD >";
        }
    };

}

#endif