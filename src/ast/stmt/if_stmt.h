#ifndef AST_IF_STMT_H
#define AST_IF_STMT_H

#include "stmt.h"
#include "../expr/expr.h"
#include "../list/list.h"
#include <memory>

namespace ASTs
{
    class IfStmt : public Stmt
    {
        public:
        IfStmt(Expr *cond, Stmt *ifStmt, List *elifList, Stmt *elseStmt) : 
        cond{cond}, ifStmt{ifStmt}, elifList{elifList}, elseStmt{elseStmt}
        {

        }

        std::unique_ptr<Expr> cond;
        std::unique_ptr<Stmt> ifStmt, elseStmt;
        std::unique_ptr<List> elifList;

    };
}

#endif