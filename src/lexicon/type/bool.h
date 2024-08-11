#ifndef LEX_BOOL_H
#define LEX_BOOL_H

#include "../lexicon.h"

namespace Lexicons
{
    class Bool : public Lexicon
    {
        public:
        bool value;
        Bool(bool value, int lineNo, int charNo) : Lexicon{Lexicon::BOOL, lineNo, charNo}, value{value}
        {

        }

        std::string const ToString() const override
        {
            if(value)
            {
                return "< BOOL, true >";
            }
            else
            {
                return "< BOOL, false >";
            }
        }
    };

}


#endif