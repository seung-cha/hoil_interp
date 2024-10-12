#ifndef AST_VAR_DECL_H
#define AST_VAR_DECL_H

#include "decl.h"
#include "../type/type.h"
#include "../list/list.h"
#include <memory>

namespace ASTs
{
    class VarDecl : public Decl
    {
        public:
        VarDecl(Type *type, List *decl) : type{type}, decl{decl}
        {

        }

        void Print(int ident) override
        {
            PrintIdent(ident);
            std::cout << "<Variable Declaration>" << std::endl;
            type->Print(ident + 1);
            decl->Print(ident + 1);
        }

        std::unique_ptr<Type> type;
        std::unique_ptr<List> decl;
    };
}


#endif