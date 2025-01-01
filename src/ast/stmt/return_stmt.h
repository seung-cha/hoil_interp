#ifndef AST_RETURN_STMT_H
#define AST_RETURN_STMT_H

#include "stmt.h"
#include "../expr/expr.h"
#include <memory>

namespace ASTs
{
    class ReturnStmt : public Stmt
    {
        public:
        ReturnStmt(Expr *expr, int lineNo, int charNo) : expr{expr}, Stmt{lineNo, charNo}
        {

        }

        AST *Visit(Visitor *visitor, AST *obj) override
        {
            return visitor->VisitReturnStmt(this, obj);
        }

        void Print(int ident) override
        {
            PrintIdent(ident);
            std::cout << "<Return Stmt>" << std::endl;
            expr->Print(ident + 1);
        }

        std::unique_ptr<Expr> expr;


    };

}

#endif