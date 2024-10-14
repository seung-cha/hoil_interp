#ifndef AST_BLOCK_ITEM_LIST_H
#define AST_BLOCK_ITEM_LIST_H

#include "list.h"
#include "block.h"
#include <memory>

namespace ASTs
{
    class BlockItemList : public List
    {
        public:
        BlockItemList(Block *block, List *next) : block{block}, next{next}
        {

        }

        void Visit(Visitor *visitor) override
        {
            visitor->VisitBlockItemList(this);
        }

        void Print(int ident) override
        {
            PrintIdent(ident);
            std::cout << "<Block Item List>" << std::endl;
            block->Print(ident + 1);
            next->Print(ident);
        }

        std::unique_ptr<Block> block;
        std::unique_ptr<List> next;
    };
}

#endif