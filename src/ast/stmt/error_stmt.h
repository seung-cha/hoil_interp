#ifndef AST_ERR_STMT_H
#define AST_ERR_STMT_H

#include "stmt.h"

namespace ASTs
{
    class ErrorStmt : public Stmt
    {
        public:
        void Print(int ident) override
        {
            PrintIdent(ident);
            std::cout << "<Error Stmt>" << std::endl;
        }
        
    };

}

#endif