#ifndef LEX_BOOL_H
#define LEX_BOOL_H

#include "../lexicon.h"

namespace Lexicons
{
    class Bool : public Lexicon
    {
        public:
        Bool(int lineNo, int charNo) : Lexicon{Lexicon::BOOL, "bool", lineNo, charNo}
        {

        }

        std::string const ToString() const override
        {
            return "< BOOL, TYPE >";
        }
    };

}


#endif