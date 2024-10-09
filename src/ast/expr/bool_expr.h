#ifndef AST_BOOL_EXPR_H
#define AST_BOOL_EXPR_H

#include "expr.h"
#include "../literal/bool_literal.h"
#include <memory>

namespace ASTs
{
    class BoolExpr : public Expr
    {
        public:
        BoolExpr(BoolLiteral *literal) : literal{literal}
        {

        }
        
        std::unique_ptr<BoolLiteral> literal;
    };
}

#endif