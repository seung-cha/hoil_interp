#ifndef AST_ELIF_STMT_H
#define AST_ELIF_STMT_H

#include "stmt.h"
#include "../expr/expr.h"
#include <memory>

namespace ASTs
{
    class ElifStmt : public Stmt
    {
        public:
        ElifStmt(Expr *cond, Stmt *stmt): cond{cond}, stmt{stmt}
        {

        }

        std::unique_ptr<Expr> cond;
        std::unique_ptr<Stmt> stmt;
    };
}

#endif