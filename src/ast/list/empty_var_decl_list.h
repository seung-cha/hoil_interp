#ifndef AST_EMPTY_VAR_DECL_LIST_H
#define AST_EMPTY_VAR_DECL_LIST_H

#include "list.h"


namespace ASTs
{
    class EmptyVarDeclList : public List
    {
        public:

        void Visit(Visitor *visitor) override
        {
            visitor->VisitEmptyVarDeclList(this);
        }

        void Print(int ident) override
        {
            PrintIdent(ident);
            std::cout << "<Empty Variable Declaration List>" << std::endl;
        }
    };
}

#endif