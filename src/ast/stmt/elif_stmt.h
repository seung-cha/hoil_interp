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

        void Visit(Visitor *visitor) override
        {
            visitor->VisitElifStmt(this);
        }

        void Print(int ident) override
        {
            PrintIdent(ident);
            std::cout << "<Elif Stmt>" << std::endl;
            cond->Print(ident + 1);
            stmt->Print(ident + 1); 
        }

        std::unique_ptr<Expr> cond;
        std::unique_ptr<Stmt> stmt;
    };
}

#endif