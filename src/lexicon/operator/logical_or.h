#ifndef LEX_LOGICAL_OR_H
#define LEX_LOGICAL_OR_H

#include "../lexicon.h"

namespace Lexicons
{
    class LogicalOr : public Lexicon
    {
        public:
        LogicalOr(int lineNo, int charNo) : Lexicon{Lexicon::LOGICAL_OR, "||", lineNo, charNo}
        {

        }

        std::string const ToString() const override
        {
            return "< LOGICAL_OR , || >";
        }
    };
}


#endif