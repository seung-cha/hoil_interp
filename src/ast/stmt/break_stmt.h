#ifndef AST_BREAK_STMT_H
#define AST_BREAK_STMT_H

#include "stmt.h"

namespace ASTs
{
    class BreakStmt : public Stmt
    {
        public:

        AST *Visit(Visitor *visitor, AST *obj) override
        {
            return visitor->VisitBreakStmt(this, obj);
        }

        void Print(int ident) override
        {
            PrintIdent(ident);
            std::cout << "<Break Stmt>" << std::endl;
        }
        
    };

}

#endif