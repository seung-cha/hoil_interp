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

        std::unique_ptr<Block> block;
        std::unique_ptr<List> next;
    };
}

#endif