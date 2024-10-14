#ifndef AST_CONTINUE_STMT_H
#define AST_CONTINUE_STMT_H

#include "stmt.h"

namespace ASTs
{
    class ContinueStmt : public Stmt
    {
        public:

        void Visit(Visitor *visitor) override
        {
            visitor->VisitContinueStmt(this);
        }

        void Print(int ident) override
        {
            PrintIdent(ident);
            std::cout << "<Continue Stmt>" << std::endl;
        }
    };

}

#endif