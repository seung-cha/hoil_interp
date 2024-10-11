#ifndef AST_ELIF_STMT_H
#define AST_ELIF_STMT_H

#include "stmt.h"
#include "../list/list.h"
#include "../expr/expr.h"
#include <memory>

namespace ASTs
{
    class ElifStmt : public Stmt
    {
        public:
        ElifStmt(Expr *cond, Stmt *stmt, List *next): cond{cond}, stmt{stmt}, next{next}
        {

        }

        std::unique_ptr<Expr> cond;
        std::unique_ptr<Stmt> stmt;
        std::unique_ptr<List> next;

    };
}

#endif