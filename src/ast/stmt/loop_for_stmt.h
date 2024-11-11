#ifndef AST_LOOP_FOR_STMT
#define AST_LOOP_FOR_STMT

#include "stmt.h"
#include "../expr/expr.h"
#include "../list/list.h"
#include <memory>

namespace ASTs
{
    class ForStmt : public Stmt
    {
        public:
        ForStmt(List *list, Stmt *cond, Expr *postOp, Stmt *body, int lineNo, int charNo) : list{list}, cond{cond},
        postOp{postOp}, body{body}, Stmt{lineNo, charNo}
        {

        }

        AST *Visit(Visitor *visitor, AST *obj) override
        {
            return visitor->VisitForStmt(this, obj);
        }

        void Print(int ident) override
        {
            PrintIdent(ident);
            std::cout << "<For Stmt>" << std::endl;
            list->Print(ident + 1);
            cond->Print(ident + 1);
            postOp->Print(ident + 1);
            body->Print(ident + 1);
        }

        std::unique_ptr<List> list;
        std::unique_ptr<Stmt> cond;
        std::unique_ptr<Expr> postOp;
        std::unique_ptr<Stmt> body;

    };
}

#endif