#ifndef LEX_INSTRUCT_H
#define LEX_INSTRUCT_H

#include "../lexicon.h"

typedef int8_t InstructType;

namespace Lexicons
{
    class Instruct : public Lexicon
    {

        public:
        static const InstructType Type_None = 0, Type_Conditional = 1, Type_Loop = 2, Type_Expr = 4;

    public:
        std::string const value;
        InstructType type = Instruct::Type_None;

        Instruct(std::string const value, int lineNo, int charNo) : Lexicon{Lexicon::INSTRUCT, value, lineNo, charNo}, value{value}
        {
        }

        std::string const ToString() const override
        {
            char str[1024 + value.size()];
            snprintf(str, 1024 + sizeof(value), "< INSTRUCT_VALUE, %s >", value.c_str());
            return str;
        }
    };

}

#endif