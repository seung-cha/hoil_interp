#ifndef AST_VAR_DECL_LIST_BLOCK_H
#define AST_VAR_DECL_LIST_BLOCK_H

#include "block.h"
#include "list.h"
#include <memory>

namespace ASTs
{
    class VarDeclListBlock : public Block
    {
        public:
        VarDeclListBlock(List *list, int lineNo, int charNo) : list{list}, Block{lineNo, charNo}
        {

        }

        AST *Visit(Visitor *visitor, AST *obj) override
        {
            return visitor->VisitVarDeclListBlock(this, obj);
        }

        void Print(int ident) override
        {
            PrintIdent(ident);
            std::cout << "<Variable Declaration Block>" << std::endl;
            list->Print(ident + 1);
        }

        std::unique_ptr<List> list;
    };
}


#endif