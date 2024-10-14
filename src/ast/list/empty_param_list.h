#ifndef AST_EMPTY_PARAM_LIST_H
#define AST_EMPTY_PARAM_LIST_H

#include "list.h"

namespace ASTs
{
    class EmptyParamList : public List
    {
        public:

        void Visit(Visitor *visitor) override
        {
            visitor->VisitEmptyParamList(this);
        }


        void Print(int ident) override
        {
            PrintIdent(ident);
            std::cout << "<Empty Parameter List>" << std::endl;
        }

    };
}

#endif