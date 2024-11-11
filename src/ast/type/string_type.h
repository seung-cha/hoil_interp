#ifndef AST_STRING_TYPE_H
#define AST_STRING_TYPE_H

#include "type.h"

namespace ASTs
{
    class StringType : public Type
    {
        public:
        StringType(int lineNo, int charNo) : Type{VarType::STRING, lineNo, charNo}
        {
            
        }

        AST *Visit(Visitor *visitor, AST *obj) override
        {
            return visitor->VisitStringType(this, obj);
        }

        void Print(int ident) override
        {
            PrintIdent(ident);
            std::cout << "<String Type>" << std::endl;
        }

        std::unique_ptr<Type> DeepCopy() override
        {
            return std::make_unique<StringType>(lineNo, charNo);
        }

        virtual bool Compatible(Type *type)
        {
            return type->IsStringType() || type->IsErrorType();
        }

    };
}

#endif