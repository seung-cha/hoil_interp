#ifndef LEX_ATTRIB_H
#define LEX_ATTRIB_H

#include "../lexicon.h"

namespace Lexicons
{
    class Attribute : public Lexicon
    {
        public:
        Attribute(int lineNo, int charNo) : Lexicon{Lexicon::ATTRIBUTE, "attribute", lineNo, charNo}
        {

        }

        std::string const ToString() const override
        {
            return "< ATTRIBUTE, TYPE >";
        }
    };

}


#endif