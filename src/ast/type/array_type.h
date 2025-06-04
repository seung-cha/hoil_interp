#ifndef AST_ARRAY_TYPE_H
#define AST_ARRAY_TYPE_H

#include "type.h"

namespace ASTs
{
    class ArrayType : public Type
    {
        public:
        ArrayType(int lineNo, int charNo) : Type{VarType::ARRAY, lineNo, charNo}
        {
            
        }

        AST *Visit(Visitor *visitor, AST *obj) override
        {
            return visitor->VisitArrayType(this, obj);
        }

        void Print(int ident) override
        {
            PrintIdent(ident);
            std::cout << "<Array Type>" << std::endl;
        }

        std::unique_ptr<Type> DeepCopy() override
        {
            return std::make_unique<ArrayType>(lineNo, charNo);
        }

        virtual bool Compatible(Type *type)
        {
            return true;
        }
    };
}

#endif