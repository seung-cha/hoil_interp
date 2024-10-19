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
        VarDecl(Type *type, List *list) : type{type}, list{list}
        {

        }

        void Visit(Visitor *visitor) override
        {
            visitor->VisitVarDecl(this);
        }

        void Print(int ident) override
        {
            PrintIdent(ident);
            std::cout << "<Variable Declaration>" << std::endl;
            type->Print(ident + 1);
            list->Print(ident + 1);
        }

        std::unique_ptr<Type> type;
        std::unique_ptr<List> list;
    };
}


#endif