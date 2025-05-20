#ifndef LEX_INSTRUCT_H
#define LEX_INSTRUCT_H

#include "../lexicon.h"

typedef int8_t InstructType;

namespace Lexicons
{
    class Instruct : public Lexicon
    {

        public:
        static const InstructType None = 0, For = 1, While = 2, Assign = 3, Decl = 4;

    public:
        std::string const value;
        InstructType type = Instruct::None;

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