#ifndef AST_STRING_TYPE_H
#define AST_STRING_TYPE_H

#include "type.h"

namespace ASTs
{
    class StringType : public Type
    {
        public:
        void Print(int ident) override
        {
            PrintIdent(ident);
            std::cout << "<String Type>" << std::endl;
        }
    };
}

#endif