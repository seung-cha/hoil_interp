#ifndef AST_INT_TYPE_H
#define AST_INT_TYPE_H

#include "type.h"

namespace ASTs
{
    class IntType : public Type
    {
        public:
        IntType() : Type{VarType::INT}
        {
            
        }

        AST *Visit(Visitor *visitor, AST *obj) override
        {
            return visitor->VisitIntType(this, obj);
        }

        void Print(int ident) override
        {
            PrintIdent(ident);
            std::cout << "<Int Type>" << std::endl;
        }

        std::unique_ptr<Type> DeepCopy() override
        {
            return std::make_unique<IntType>();
        }

        virtual bool Compatible(Type *type)
        {
            return type->IsIntType() || type->IsErrorType() || type->IsRealType();
        }


    };
}

#endif