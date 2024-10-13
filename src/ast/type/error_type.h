#ifndef AST_ERR_TYPE_H
#define AST_ERR_TYPE_H

#include "type.h"

namespace ASTs
{
    class ErrorType : public Type
    {
        public:
        void Print(int ident) override
        {
            PrintIdent(ident);
            std::cout << "<Error Type>" << std::endl;
        }
    };
}

#endif