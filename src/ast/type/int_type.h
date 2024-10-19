#ifndef AST_INT_TYPE_H
#define AST_INT_TYPE_H

#include "type.h"

namespace ASTs
{
    class IntType : public Type
    {
        public:

        AST *Visit(Visitor *visitor, AST *obj) override
        {
            return visitor->VisitIntType(this, obj);
        }

        void Print(int ident) override
        {
            PrintIdent(ident);
            std::cout << "<Int Type>" << std::endl;
        }
    };
}

#endif