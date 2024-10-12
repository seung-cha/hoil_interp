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

        std::unique_ptr<Identifier> identifier;
        std::unique_ptr<Expr> expr;
    };

}

#endif