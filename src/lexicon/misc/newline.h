#ifndef LEX_NEWLINE_H
#define LEX_NEWLINE_H

#include "../lexicon.h"

namespace Lexicons
{
    class Newline : public Lexicon
    {
        public:
        Newline(int lineNo, int charNo) : Lexicon{Lexicon::NEWLINE, "\\n", lineNo, charNo}
        {

        }

        std::string const ToString() const override
        {
            return "< NEWLINE, \\n >";
        }
    };

}


#endif