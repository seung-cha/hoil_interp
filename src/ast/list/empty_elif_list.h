#ifndef AST_EMPTY_ELIF_LIST_H
#define AST_EMPTY_ELIF_LIST_H

#include "list.h"
#include "../stmt/stmt.h"
#include <memory>

namespace ASTs
{
    class EmptyElifList : public List
    {
        public:

        AST *Visit(Visitor *visitor, AST *obj) override
        {
            return visitor->VisitEmptyElifList(this, obj);
        }


        void Print(int ident) override
        {
            PrintIdent(ident);
            std::cout << "<Empty Elif List>" << std::endl;
        }
    };
}

#endif