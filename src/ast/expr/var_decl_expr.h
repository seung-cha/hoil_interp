#ifndef AST_VAR_DELC_EXPR_H
#define AST_VAR_DELC_EXPR_H

#include "expr.h"
#include <memory>

namespace ASTs
{
    class VarDeclExpr : public Expr
    {
        public:
        VarDeclExpr(Expr *expr) : expr{expr}
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
            expr->Print(ident + 1);
        }

        std::unique_ptr<Expr> expr;
    };

}

#endif