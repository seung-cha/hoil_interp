#ifndef AST_BOOL_TYPE_H
#define AST_BOOL_TYPE_H

#include "type.h"

namespace ASTs
{
    class BoolType : public Type
    {
        public:
        BoolType() : Type{VarType::BOOL}
        {
            
        }

        AST *Visit(Visitor *visitor, AST *obj) override
        {
            return visitor->VisitBoolType(this, obj);
        }

        void Print(int ident) override
        {
            PrintIdent(ident);
            std::cout << "<Bool Type>" << std::endl;
        }
    };
}

#endif