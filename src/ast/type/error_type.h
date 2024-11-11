#ifndef AST_ERR_TYPE_H
#define AST_ERR_TYPE_H

#include "type.h"

namespace ASTs
{
    class ErrorType : public Type
    {
        public:
        ErrorType(int lineNo, int charNo) : Type{VarType::ERROR, lineNo, charNo}
        {
            
        }

        AST *Visit(Visitor *visitor, AST *obj) override
        {
            return visitor->VisitErrorType(this, obj);
        }

        void Print(int ident) override
        {
            PrintIdent(ident);
            std::cout << "<Error Type>" << std::endl;
        }

        std::unique_ptr<Type> DeepCopy() override
        {
            return std::make_unique<ErrorType>(lineNo, charNo);
        }

        virtual bool Compatible(Type *type)
        {
            return true;
        }
    };
}

#endif