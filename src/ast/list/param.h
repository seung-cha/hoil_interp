#ifndef AST_PARAM_H
#define AST_PARAM_H

#include "../ast.h"
#include "../type/type.h"
#include "../identifier.h"
#include <memory>

namespace ASTs
{
    class Param : public AST
    {
        public:
        Param(Type *type, Identifier *identifier) : type{type}, identifier{identifier}
        {

        }

        void Print(int ident) override
        {
            PrintIdent(ident);
            std::cout << "<Param>" << std::endl;
            type->Print(ident + 1);
            identifier->Print(ident + 1);
        }

        std::unique_ptr<Type> type;
        std::unique_ptr<Identifier> identifier;
    };
}

#endif
