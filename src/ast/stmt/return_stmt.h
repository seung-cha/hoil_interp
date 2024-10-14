#ifndef AST_RETURN_STMT_H
#define AST_RETURN_STMT_H

#include "stmt.h"
#include <memory>

namespace ASTs
{
    class ReturnStmt : public Stmt
    {
        public:
        ReturnStmt(Stmt *stmt) : stmt{stmt}
        {

        }

        void Visit(Visitor *visitor) override
        {
            visitor->VisitReturnStmt(this);
        }

        void Print(int ident) override
        {
            PrintIdent(ident);
            std::cout << "<Return Stmt>" << std::endl;
            stmt->Print(ident + 1);
        }

        std::unique_ptr<Stmt> stmt;


    };

}

#endif