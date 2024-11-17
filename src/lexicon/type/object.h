#ifndef LEX_OBJ_H
#define LEX_OBJ_H

#include "../lexicon.h"

namespace Lexicons
{
    class Object : public Lexicon
    {
        public:
        Object(int lineNo, int charNo) : Lexicon{Lexicon::OBJECT, "object", lineNo, charNo}
        {

        }

        std::string const ToString() const override
        {
            return "< OBJECT, TYPE >";
        }
    };

}


#endif