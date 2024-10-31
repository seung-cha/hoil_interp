#ifndef AST_ERR_STMT_H
#define AST_ERR_STMT_H

#include "stmt.h"

namespace ASTs
{
    class ErrorStmt : public Stmt
    {
        public:

        AST *Visit(Visitor *visitor, AST *obj) override
        {
            return visitor->VisitErrorStmt(this, obj);
        }

        void Print(int ident) override
        {
            PrintIdent(ident);
            std::cout << "<Error Stmt>" << std::endl;
        }
        
    };

}

#endif