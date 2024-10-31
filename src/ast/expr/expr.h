#ifndef AST_EXPR_H
#define AST_EXPR_H

#include "../ast.h"
#include "../type/type.h"
#include <memory>

namespace ASTs
{
    class Expr : public AST
    {
        public:
        std::unique_ptr<Type> type{};
    };
}

#endif