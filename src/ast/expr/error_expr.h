#ifndef AST_ERR_EXPR_H
#define AST_ERR_EXPR_H

#include "expr.h"
#include "../op/operator.h"
#include <memory>

namespace ASTs
{
    class ErrorExpr : public Expr
    {
        public:

        void Print(int ident) override
        {
            PrintIdent(ident);
            std::cout << "<Error Expression>" << std::endl;

        }

    };
}

#endif