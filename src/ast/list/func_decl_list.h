#ifndef AST_FUNC_DECL_LIST_H
#define AST_FUNC_DECL_LIST_H

#include "list.h"
#include "../decl/decl.h"
#include <memory>

namespace ASTs
{
    class FuncDeclList : public List
    {
        public:
        FuncDeclList(Decl *decl, List *list) : decl{decl}, list{list}
        {

        }

        std::unique_ptr<Decl> decl;
        std::unique_ptr<List> list;
    };
}

#endif