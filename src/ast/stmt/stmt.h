#ifndef AST_STMT_H
#define AST_STMT_H

#include "../ast.h"

namespace ASTs
{
    class Stmt : public AST
    {
        public:
        bool isLoopBody = false;
        bool isFuncBody = false;
        bool isLoopStmt = false;
        bool isFuncStmt = false;
    };
}

#endif