#ifndef AST_BOOL_TYPE_H
#define AST_BOOL_TYPE_H

#include "type.h"

namespace ASTs
{
    class BoolType : public Type
    {
        public:
        BoolType(int lineNo, int charNo) : Type{VarType::BOOL, lineNo, charNo}
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

        std::unique_ptr<Type> DeepCopy() override
        {
            return std::make_unique<BoolType>(lineNo, charNo);
        }

        virtual bool Compatible(Type *type)
        {
            return type->IsBoolType() || type->IsErrorType();
        }
    };
}

#endif