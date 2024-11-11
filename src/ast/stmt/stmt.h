#ifndef AST_STMT_H
#define AST_STMT_H

#include "../ast.h"

namespace ASTs
{
    class Stmt : public AST
    {
        public:
        Stmt(int lineNo, int charNo) : AST{lineNo, charNo}
        {

        }
        
        bool isLoopBody = false;
        bool isFuncBody = false;
        bool isLoopStmt = false;
        bool isFuncStmt = false;
    };
}

#endif