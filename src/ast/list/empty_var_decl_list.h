#ifndef AST_EMPTY_VAR_DECL_LIST_H
#define AST_EMPTY_VAR_DECL_LIST_H

#include "list.h"


namespace ASTs
{
    class EmptyVarDeclList : public List
    {
        public:

        AST *Visit(Visitor *visitor, AST *obj) override
        {
            return visitor->VisitEmptyVarDeclList(this, obj);
        }

        void Print(int ident) override
        {
            PrintIdent(ident);
            std::cout << "<Empty Variable Declaration List>" << std::endl;
        }
    };
}

#endif