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

        void Print(int ident) override
        {
            PrintIdent(ident);
            std::cout << "<Function Declaration List>" << std::endl;
            decl->Print(ident + 1);
            list->Print(ident + 1);
        }

        std::unique_ptr<Decl> decl;
        std::unique_ptr<List> list;
    };
}

#endif