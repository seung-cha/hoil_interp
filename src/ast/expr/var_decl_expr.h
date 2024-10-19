#ifndef AST_VAR_DELC_EXPR_H
#define AST_VAR_DELC_EXPR_H

#include "expr.h"
#include "../identifier.h"
#include <memory>

namespace ASTs
{
    class VarDeclExpr : public Expr
    {
        public:
        VarDeclExpr(Identifier *identifier, Expr *expr) : identifier{identifier}, expr{expr}
        {

        }

        AST *Visit(Visitor *visitor, AST *obj) override
        {
            return visitor->VisitVarDeclExpr(this, obj);
        }
        
        void Print(int ident) override
        {
            PrintIdent(ident);
            std::cout << "<Variable Declaration Expression>" << std::endl;
            identifier->Print(ident + 1);
            expr->Print(ident + 1);
        }

        std::unique_ptr<Identifier> identifier;
        std::unique_ptr<Expr> expr;
    };

}

#endif