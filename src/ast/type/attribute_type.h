#ifndef AST_ATTRIB_TYPE_H
#define AST_ATTRIB_TYPE_H

#include "type.h"

namespace ASTs
{
    class AttributeType : public Type
    {
        public:
        AttributeType(int lineNo, int charNo) : Type{VarType::ATTRIBUTE, lineNo, charNo}
        {
            
        }

        AST *Visit(Visitor *visitor, AST *obj) override
        {
            return visitor->VisitAttributeType(this, obj);
        }

        void Print(int ident) override
        {
            PrintIdent(ident);
            std::cout << "<Attribute Type>" << std::endl;
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