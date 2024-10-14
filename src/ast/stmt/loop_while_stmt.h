#ifndef AST_LOOP_WHILE_STMT
#define AST_LOOP_WHILE_STMT

#include "stmt.h"
#include "../expr/expr.h"
#include "../list/list.h"
#include <memory>

namespace ASTs
{
    class WhileStmt : public Stmt
    {
        public:
        WhileStmt(Expr *cond, Stmt *stmt) : cond{cond}, stmt{stmt}
        {

        }

        void Visit(Visitor *visitor) override
        {
            visitor->VisitWhileStmt(this);
        }

        void Print(int ident) override
        {
            PrintIdent(ident);
            std::cout << "<While Stmt>" << std::endl;
            cond->Print(ident + 1);
            stmt->Print(ident + 1);
        }

        std::unique_ptr<Expr> cond;
        std::unique_ptr<Stmt> stmt;
    };
}

#endif