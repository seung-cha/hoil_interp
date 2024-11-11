#ifndef AST_BLOCK_H
#define AST_BLOCK_H

#include "../ast.h"

namespace ASTs
{
    class Block : public AST
    {
        public:
        Block(int lineNo, int charNo) : AST{lineNo, charNo}
        {

        }
        
    };
}


#endif