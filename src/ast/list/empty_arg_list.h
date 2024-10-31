#ifndef AST_EMPTY_ARG_LIST_H
#define AST_EMPTY_ARG_LIST_H

#include "list.h"

namespace ASTs
{
    class EmptyArgList : public List
    {
        public:

        AST *Visit(Visitor *visitor, AST *obj) override
        {
            return visitor->VisitEmptyArgList(this, obj);
        }

        void Print(int ident) override
        {
            PrintIdent(ident);
            std::cout << "<Empty Arg List>" << std::endl;
        }

    };
}

#endif