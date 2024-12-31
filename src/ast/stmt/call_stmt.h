#ifndef AST_CALL_STMT_H
#define AST_CALL_STMT_H

#include "stmt.h"
#include "../expr/expr.h"
#include <memory>

namespace ASTs
{
    class CallStmt : public Stmt
    {
        public:
        CallStmt(ASTs::Expr *callExpr, int lineNo, int charNo) : Stmt{lineNo, charNo}, expr{callExpr}
        {
            
        }

        AST *Visit(Visitor *visitor, AST *obj) override
        {
            return visitor->VisitCallStmt(this, obj);
        }

        void Print(int ident) override
        {
            PrintIdent(ident);
            std::cout << "<Break Stmt>" << std::endl;
        }

        std::unique_ptr<ASTs::Expr> expr;
        
    };

}

#endif