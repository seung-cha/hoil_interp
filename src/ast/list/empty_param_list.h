#ifndef AST_EMPTY_PARAM_LIST_H
#define AST_EMPTY_PARAM_LIST_H

#include "list.h"

namespace ASTs
{
    class EmptyParamList : public List
    {
        public:

        AST *Visit(Visitor *visitor, AST *obj) override
        {
            return visitor->VisitEmptyParamList(this, obj);
        }


        void Print(int ident) override
        {
            PrintIdent(ident);
            std::cout << "<Empty Parameter List>" << std::endl;
        }

    };
}

#endif