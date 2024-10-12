#ifndef AST_EMPTY_STMT_H
#define AST_EMPTY_STMT_H

#include "stmt.h"

namespace ASTs
{
    class EmptyStmt : public Stmt
    {
        public:
        void Print(int ident) override
        {
            PrintIdent(ident);
            std::cout << "<Empty Stmt>" << std::endl;

        }

    };
}

#endif