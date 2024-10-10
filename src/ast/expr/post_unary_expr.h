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
        
        std::unique_ptr<Expr> expr;
        std::unique_ptr<Operator> op;

    };
}


#endif