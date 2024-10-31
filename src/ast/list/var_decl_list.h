#ifndef AST_VAR_DECL_LIST_H
#define AST_VAR_DECL_LIST_H

#include "list.h"
#include "../expr/expr.h"
#include "../identifier.h"
#include "../decl/decl.h"
#include <memory>

namespace ASTs
{
    class VarDeclList : public List
    {
        public:
        VarDeclList(Decl *decl, List *next) : decl{decl}, next{next}
        {

        }

        AST *Visit(Visitor *visitor, AST *obj) override
        {
            return visitor->VisitVarDeclList(this, obj);
        }

        void Print(int ident) override
        {
            PrintIdent(ident);
            std::cout << "<Variable Declaration List>" << std::endl;
            decl->Print(ident + 1);
            next->Print(ident); 
        }

        std::unique_ptr<Decl> decl;
        std::unique_ptr<List> next;
    };
}

#endif