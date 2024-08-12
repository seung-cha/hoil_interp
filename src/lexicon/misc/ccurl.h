#ifndef LEX_CLOSE_CURLY_H
#define LEX_CLOSE_CURLY_H

#include "../lexicon.h"

namespace Lexicons
{
    class CloseCurly : public Lexicon
    {
        public:
        CloseCurly(int lineNo, int charNo) : Lexicon{Lexicon::CCURLY, lineNo, charNo}
        {

        }

        std::string const ToString() const override
        {
            return "< CCURLY, } >";
        }
    };

}


#endif