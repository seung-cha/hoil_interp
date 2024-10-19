#ifndef AST_REAL_TYPE_H
#define AST_REAL_TYPE_H

#include "type.h"

namespace ASTs
{
    class RealType : public Type
    {
        public:

        AST *Visit(Visitor *visitor, AST *obj) override
        {
            return visitor->VisitRealType(this, obj);
        }

        void Print(int ident) override
        {
            PrintIdent(ident);
            std::cout << "<Real Type>" << std::endl;
        }
    };
}

#endif