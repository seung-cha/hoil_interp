#ifndef AST_EMPTY_FUNC_DECL_LIST_H
#define AST_EMPTY_FUNC_DECL_LIST_H

#include "list.h"

namespace ASTs
{
    class EmptyFuncDeclList : public List
    {
        public:

        AST *Visit(Visitor *visitor, AST *obj) override
        {
            return visitor->VisitEmptyFuncDeclList(this, obj);
        }

        void Print(int ident) override
        {
            PrintIdent(ident);
            std::cout << "<Empty Function Declaration List>" << std::endl;
        }
    };
}

#endif