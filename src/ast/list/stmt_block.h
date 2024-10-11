#ifndef AST_STMT_BLOCK_H
#define AST_STMT_BLOCK_H

#include "../stmt/stmt.h"
#include "block.h"
#include "list.h"
#include <memory>

namespace ASTs
{
    class StmtBlock : public Block
    {
        public:
        StmtBlock(Stmt *stmt, List *next) : stmt{stmt}, next{next}
        {

        }

        std::unique_ptr<Stmt> stmt;
        std::unique_ptr<List> next;

    };
}


#endif