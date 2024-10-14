#ifndef AST_INT_TYPE_H
#define AST_INT_TYPE_H

#include "type.h"

namespace ASTs
{
    class IntType : public Type
    {
        public:

        void Visit(Visitor *visitor) override
        {
            visitor->VisitIntType(this);
        }

        void Print(int ident) override
        {
            PrintIdent(ident);
            std::cout << "<Int Type>" << std::endl;
        }
    };
}

#endif