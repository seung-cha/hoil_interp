#ifndef LEX_IS_H
#define LEX_IS_H

#include "../lexicon.h"

namespace Lexicons
{
    class Is : public Lexicon
    {
        public:
        Is(int lineNo, int charNo) : Lexicon{Lexicon::IS, "is", lineNo, charNo}
        {

        }

        std::string const ToString() const override
        {
            return "< IS, is >";
        }
    };

}


#endif