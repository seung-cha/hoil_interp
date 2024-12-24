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
        Expr()
        {

        }
        Expr(int lineNo, int charNo) : AST{lineNo, charNo}
        {

        }

        std::unique_ptr<Type> type{};
        bool assignable = false;
        bool isEmptyExpr = false;
    };
}

#endif