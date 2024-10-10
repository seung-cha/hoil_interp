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
        PostUnaryExpr(std::unique_ptr<Expr> expr, std::unique_ptr<Operator> op) : expr{std::move(expr)}, op{std::move(op)}
        {

        }
        
        std::unique_ptr<Expr> expr;
        std::unique_ptr<Operator> op;

    };
}


#endif