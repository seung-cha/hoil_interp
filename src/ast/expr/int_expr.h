#ifndef AST_INT_EXPR_H
#define AST_INT_EXPR_H

#include "expr.h"
#include "../literal/int_literal.h"
#include <memory>

namespace ASTs
{
    class IntExpr : public Expr
    {
        public:
        IntExpr(IntLiteral *literal) : literal{literal}
        {

        }
        std::unique_ptr<IntLiteral> literal;
    };
}

#endif