#ifndef AST_VAR_EXPR_H
#define AST_VAR_EXPR_H

#include "expr.h"
#include "../var/Variable.h"
#include <memory>

namespace ASTs
{
    class VariableExpr : public Expr
    {
        public:
        VariableExpr(std::unique_ptr<Variable> variable) : variable{std::move(variable)}
        {

        }
        
        std::unique_ptr<Variable> variable;
    };

}

#endif