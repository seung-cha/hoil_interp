#ifndef AST_VOID_TYPE_H
#define AST_VOID_TYPE_H

#include "type.h"

namespace ASTs
{
    class VoidType : public Type
    {
        public:
        VoidType() : Type{VarType::VOID}
        {
            
        }

        AST *Visit(Visitor *visitor, AST *obj) override
        {
            return visitor->VisitVoidType(this, obj);
        }

        void Print(int ident) override
        {
            PrintIdent(ident);
            std::cout << "<Void Type>" << std::endl;
        }
    };
}

#endif