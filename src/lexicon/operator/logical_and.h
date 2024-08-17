#ifndef LEX_LOGICAL_AND_H
#define LEX_LOGICAL_AND_H

#include "../lexicon.h"

namespace Lexicons
{
    class LogicalAnd : public Lexicon
    {
        public:
        LogicalAnd(int lineNo, int charNo) : Lexicon{Lexicon::LOGICAL_AND, lineNo, charNo}
        {

        }

        std::string const ToString() const override
        {
            return "< LOGICAL_AND , && >";
        }
    };
}


#endif