#ifndef AST_EMPTY_EXPR_H
#define AST_EMPTY_EXPR_H

#include "expr.h"

namespace ASTs
{
    class EmptyExpr : public Expr
    {
        public:
        void Print(int ident) override
        {
            PrintIdent(ident);
            std::cout << "<Empty Expression>" << std::endl;
        }
    };
}

#endif