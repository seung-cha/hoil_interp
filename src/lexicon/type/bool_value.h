#ifndef LEX_BOOL_VALUE_H
#define LEX_BOOL_VALUE_H

#include "../lexicon.h"

namespace Lexicons
{
    class BoolValue : public Lexicon
    {
        public:
        bool const value;
        BoolValue(bool const value, std::string spelling, int lineNo, int charNo) : 
        Lexicon{Lexicon::BOOLVAL, spelling, lineNo, charNo}, value{value}
        {
            
        }

        std::string const ToString() const override
        {
            if(value)
            {
                return "< BOOL_VALUE, true >";
            }
            else
            {
                return "< BOOL_VALUE, false >";
            }
        }
    };

}


#endif