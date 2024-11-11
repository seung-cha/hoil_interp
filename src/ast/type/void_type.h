#ifndef AST_VOID_TYPE_H
#define AST_VOID_TYPE_H

#include "type.h"

namespace ASTs
{
    class VoidType : public Type
    {
        public:
        VoidType(int lineNo, int charNo) : Type{VarType::VOID, lineNo, charNo}
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

        std::unique_ptr<Type> DeepCopy() override
        {
            return std::make_unique<VoidType>(lineNo, charNo);
        }

        virtual bool Compatible(Type *type)
        {
            return type->IsErrorType();
        }

    };
}

#endif