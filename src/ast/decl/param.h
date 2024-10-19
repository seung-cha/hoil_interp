#ifndef AST_PARAM_H
#define AST_PARAM_H

#include "../ast.h"
#include "../type/type.h"
#include "../identifier.h"
#include "decl.h"
#include <memory>

namespace ASTs
{
    class Param : public Decl
    {
        public:
        Param(Type *type, Identifier *identifier) : Decl{type, identifier}
        {

        }

        AST *Visit(Visitor *visitor, AST *obj) override
        {
            return visitor->VisitParam(this, obj);
        }

        void Print(int ident) override
        {
            PrintIdent(ident);
            std::cout << "<Param>" << std::endl;
            type->Print(ident + 1);
            identifier->Print(ident + 1);
        }
    };
}

#endif
