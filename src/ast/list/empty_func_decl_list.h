#ifndef AST_EMPTY_FUNC_DECL_LIST_H
#define AST_EMPTY_FUNC_DECL_LIST_H

#include "list.h"

namespace ASTs
{
    class EmptyFuncDeclList : public List
    {
        public:

        void Visit(Visitor *visitor) override
        {
            visitor->VisitEmptyFuncDeclList(this);
        }

        void Print(int ident) override
        {
            PrintIdent(ident);
            std::cout << "<Empty Function Declaration List>" << std::endl;
        }
    };
}

#endif