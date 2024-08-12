#ifndef LEX_OPEN_CURLY_H
#define LEX_OPEN_CURLY_H

#include "../lexicon.h"

namespace Lexicons
{
    class OpenCurly : public Lexicon
    {
        public:
        OpenCurly(int lineNo, int charNo) : Lexicon{Lexicon::OCURLY, lineNo, charNo}
        {

        }

        std::string const ToString() const override
        {
            return "< OCURLY, { >";
        }
    };

}


#endif