#ifndef AST_BOOL_TYPE_H
#define AST_BOOL_TYPE_H

#include "type.h"

namespace ASTs
{
    class BoolType : public Type
    {
        public:

        void Visit(Visitor *visitor) override
        {
            visitor->VisitBoolType(this);
        }

        void Print(int ident) override
        {
            PrintIdent(ident);
            std::cout << "<Bool Type>" << std::endl;
        }
    };
}

#endif