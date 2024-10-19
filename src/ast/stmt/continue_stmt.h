#ifndef AST_CONTINUE_STMT_H
#define AST_CONTINUE_STMT_H

#include "stmt.h"

namespace ASTs
{
    class ContinueStmt : public Stmt
    {
        public:

        AST *Visit(Visitor *visitor, AST *obj) override
        {
            return visitor->VisitContinueStmt(this, obj);
        }

        void Print(int ident) override
        {
            PrintIdent(ident);
            std::cout << "<Continue Stmt>" << std::endl;
        }
    };

}

#endif