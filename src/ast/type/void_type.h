#ifndef AST_VOID_TYPE_H
#define AST_VOID_TYPE_H

#include "type.h"

namespace ASTs
{
    class VoidType : public Type
    {
        public:

        void Visit(Visitor *visitor) override
        {
            visitor->VisitVoidType(this);
        }

        void Print(int ident) override
        {
            PrintIdent(ident);
            std::cout << "<Void Type>" << std::endl;
        }
    };
}

#endif