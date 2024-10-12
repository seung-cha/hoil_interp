#ifndef AST_VAR_DECL_LIST_H
#define AST_VAR_DECL_LIST_H

#include "list.h"
#include "../expr/expr.h"
#include "../identifier.h"
#include <memory>

namespace ASTs
{
    class VarDeclList : List
    {
        public:
        VarDeclList(Identifier *identifier, Expr *expr, List *next) : identifier{identifier}, expr{expr}, next{next}
        {

        }

        std::unique_ptr<Identifier> identifier;
        std::unique_ptr<Expr> expr;
        std::unique_ptr<List> next;
    };
}

#endif