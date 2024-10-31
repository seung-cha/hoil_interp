#ifndef AST_EXPR_STMT_H
#define AST_EXPR_STMT_H

#include "stmt.h"
#include "../expr/expr.h"
#include<memory>

namespace ASTs
{
    class ExprStmt : public Stmt
    {
        public:
        ExprStmt(Expr *expr) : expr{expr}
        {

        }
        
        AST *Visit(Visitor *visitor, AST *obj) override
        {
            return visitor->VisitExprStmt(this, obj);
        }

        void Print(int ident) override
        {
            PrintIdent(ident);
            std::cout << "<Expression Stmt>" << std::endl;
            expr->Print(ident + 1);
        }

        std::unique_ptr<Expr> expr;
    };
}


#endif