#ifndef AST_REAL_TYPE_H
#define AST_REAL_TYPE_H

#include "type.h"

namespace ASTs
{
    class RealType : public Type
    {
        public:
        RealType(int lineNo, int charNo) : Type{VarType::REAL, lineNo, charNo}
        {
            
        }

        AST *Visit(Visitor *visitor, AST *obj) override
        {
            return visitor->VisitRealType(this, obj);
        }

        void Print(int ident) override
        {
            PrintIdent(ident);
            std::cout << "<Real Type>" << std::endl;
        }

        std::unique_ptr<Type> DeepCopy() override
        {
            return std::make_unique<RealType>(lineNo, charNo);
        }

        virtual bool Compatible(Type *type)
        {
            return type->IsIntType() || type->IsErrorType() || type->IsRealType() || type->IsVoidType();
        }

    };
}

#endif