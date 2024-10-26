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
        FuncDeclList(Decl *decl, List *next) : decl{decl}, next{next}
        {

        }

        AST *Visit(Visitor *visitor, AST *obj) override
        {
            return visitor->VisitFuncDeclList(this, obj);
        }

        void Print(int ident) override
        {
            PrintIdent(ident);
            std::cout << "<Function Declaration List>" << std::endl;
            decl->Print(ident + 1);
            next->Print(ident);
        }

        std::unique_ptr<Decl> decl;
        std::unique_ptr<List> next;
    };
}

#endif