#ifndef AST_BREAK_STMT_H
#define AST_BREAK_STMT_H

#include "stmt.h"

namespace ASTs
{
    class BreakStmt : public Stmt
    {
        public:
        BreakStmt(int lineNo, int charNo) : Stmt{lineNo, charNo}
        {
            
        }

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