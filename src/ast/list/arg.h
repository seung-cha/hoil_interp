#ifndef AST_ARG_H
#define AST_ARG_H

#include "../ast.h"
#include "../expr/expr.h"
#include <memory>

namespace ASTs
{
    class Arg : public AST
    {
        public:
        Arg(Expr *expr) : expr{expr}
        {

        }

        std::unique_ptr<Expr> expr;


    };
}

#endif