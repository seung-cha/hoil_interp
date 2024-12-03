#ifndef AST_OBJECT_TYPE_H
#define AST_OBJECT_TYPE_H

#include "type.h"

namespace ASTs
{
    class ObjectType : public Type
    {
        public:
        ObjectType(int lineNo, int charNo) : Type{VarType::OBJECT, lineNo, charNo}
        {
            
        }

        AST *Visit(Visitor *visitor, AST *obj) override
        {
            return visitor->VisitObjectType(this, obj);
        }

        void Print(int ident) override
        {
            PrintIdent(ident);
            std::cout << "<Object Type>" << std::endl;
        }

        std::unique_ptr<Type> DeepCopy() override
        {
            return std::make_unique<ObjectType>(lineNo, charNo);
        }

        virtual bool Compatible(Type *type)
        {
            return type->IsBoolType() || type->IsErrorType();
        }
    };
}

#endif