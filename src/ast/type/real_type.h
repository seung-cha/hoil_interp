#ifndef AST_REAL_TYPE_H
#define AST_REAL_TYPE_H

#include "type.h"

namespace ASTs
{
    class RealType : public Type
    {
        public:

        void Visit(Visitor *visitor) override
        {
            visitor->VisitRealType(this);
        }

        void Print(int ident) override
        {
            PrintIdent(ident);
            std::cout << "<Real Type>" << std::endl;
        }
    };
}

#endif