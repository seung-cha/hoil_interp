#ifndef AST_LOOP_FOR_STMT
#define AST_LOOP_FOR_STMT

#include "stmt.h"
#include "../expr/expr.h"
#include "../list/list.h"
#include "../decl/decl.h"
#include <memory>

namespace ASTs
{
    class ForStmt : public Stmt
    {
        public:
        ForStmt(Decl *decl, Stmt *cond, Expr *postOp, Stmt *body) : decl{decl}, cond{cond},
        postOp{postOp}, body{body}
        {

        }

        void Visit(Visitor *visitor) override
        {
            visitor->VisitForStmt(this);
        }

        void Print(int ident) override
        {
            PrintIdent(ident);
            std::cout << "<For Stmt>" << std::endl;
            decl->Print(ident + 1);
            cond->Print(ident + 1);
            postOp->Print(ident + 1);
            body->Print(ident + 1);
        }

        std::unique_ptr<Decl> decl;
        std::unique_ptr<Stmt> cond;
        std::unique_ptr<Expr> postOp;
        std::unique_ptr<Stmt> body;

    };
}

#endif