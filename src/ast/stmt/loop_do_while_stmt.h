#ifndef AST_LOOP_DO_WHILE_STMT
#define AST_LOOP_DO_WHILE_STMT

#include "stmt.h"
#include "../expr/expr.h"
#include "../list/list.h"
#include <memory>

namespace ASTs
{
    class DoWhileStmt : public Stmt
    {
        public:
        DoWhileStmt(Expr *cond, Stmt *body) : body{body}, cond{cond}
        {

        }

        std::unique_ptr<Expr> cond;
        std::unique_ptr<Stmt> body;

    };
}

#endif