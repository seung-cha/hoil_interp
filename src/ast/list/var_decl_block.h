#ifndef AST_VAR_DECL_BLOCK_H
#define AST_VAR_DECL_BLOCK_H

#include "../decl/decl.h"
#include "block.h"
#include "list.h"
#include <memory>

namespace ASTs
{
    class VarDeclBlock : public Block
    {
        public:
        VarDeclBlock(Decl *decl) : decl{decl}
        {

        }

        std::unique_ptr<Decl> decl;
    };
}


#endif