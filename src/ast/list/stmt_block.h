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
        StmtBlock(Stmt *stmt) : stmt{stmt}
        {

        }

        void Print(int ident) override
        {
            PrintIdent(ident);
            std::cout << "<Stmt Block>" << std::endl;
            stmt->Print(ident + 1);
        }

        std::unique_ptr<Stmt> stmt;

    };
}


#endif