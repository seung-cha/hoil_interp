#ifndef AST_POST_UNARY_EXPR_H
#define AST_POST_UNARY_EXPR_H 

#include "expr.h"
#include "../op/operator.h"

#include <memory>

namespace ASTs
{
    class PostUnaryExpr : public Expr
    {
        public:
        PostUnaryExpr(Expr *expr, Operator *op) : expr{expr}, op{op}
        {

        }

        AST *Visit(Visitor *visitor, AST *obj) override
        {
            return visitor->VisitPostUnaryExpr(this, obj);
        }

        void Print(int ident) override
        {
            PrintIdent(ident);
            std::cout << "<Post Unary Expression>" << std::endl;
            expr->Print(ident + 1);
            op->Print(ident + 1);
        }

        std::unique_ptr<Expr> expr;
        std::unique_ptr<Operator> op;

    };
}


#endif