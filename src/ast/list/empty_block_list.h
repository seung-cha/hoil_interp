#ifndef AST_EMPTY_BLOCK_LIST_H
#define AST_EMPTY_BLOCK_LIST_H

#include "block.h"

namespace ASTs
{
    class EmptyBlockList : public List
    {
        public:
        void Print(int ident) override
        {
            PrintIdent(ident);
            std::cout << "<Empty Block List>" << std::endl;
        }
    };
}


#endif