#ifndef AST_ASSIGN_EXPR_H
#define AST_ASSIGN_EXPR_H

#include "expr.h"
#include "../op/operator.h"
#include <memory>

namespace ASTs
{
    class AssignExpr : public Expr
    {
        public:
        AssignExpr(Expr *lhs, Expr *rhs, Operator *op) : lhs{lhs}, rhs{rhs}, op{op}
        {
            
        }

        void Print(int ident) override
        {
            PrintIdent(ident);
            std::cout << "<Assignment Expression>" << std::endl;
            lhs->Print(ident + 1);
            op->Print(ident + 1);
            rhs->Print(ident + 1);
        }

        std::unique_ptr<Expr> lhs, rhs;
        std::unique_ptr<Operator> op;
    };
}

#endif