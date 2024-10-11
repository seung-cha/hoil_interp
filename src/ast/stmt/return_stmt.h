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

        std::unique_ptr<Stmt> stmt;


    };

}

#endif