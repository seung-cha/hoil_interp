#ifndef AST_STRING_TYPE_H
#define AST_STRING_TYPE_H

#include "type.h"

namespace ASTs
{
    class StringType : public Type
    {
        public:
        StringType() : Type{VarType::STRING}
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
            return std::make_unique<StringType>();
        }

    };
}

#endif