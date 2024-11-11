#ifndef AST_VAR_DECL_H
#define AST_VAR_DECL_H

#include "decl.h"
#include "../expr/expr.h"
#include <memory>

namespace ASTs
{
    class VarDecl : public Decl
    {
        public:
        VarDecl(Type *type, Identifier *identifier, Expr *expr, int lineNo, int charNo) : Decl{type, identifier, lineNo, charNo}, expr{expr}
        {

        }

        AST *Visit(Visitor *visitor, AST *obj) override
        {
            return visitor->VisitVarDecl(this, obj);
        }

        void Print(int ident) override
        {
            PrintIdent(ident);
            std::cout << "<Variable Declaration>" << std::endl;
            type->Print(ident + 1);
            identifier->Print(ident + 1);
            expr->Print(ident + 1);
        }

        std::unique_ptr<Expr> expr;
    };
}


#endif