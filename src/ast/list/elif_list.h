#ifndef AST_ELIF_LIST_H
#define AST_ELIF_LIST_H

#include "list.h"
#include "../stmt/stmt.h"
#include <memory>

namespace ASTs
{
    class ElifList : public List
    {
        public:
        ElifList(Stmt *elif, List *next) : elif{elif}, next{next}
        {

        }

        AST *Visit(Visitor *visitor, AST *obj) override
        {
            return visitor->VisitElifList(this, obj);
        }

        void Print(int ident) override
        {
            PrintIdent(ident);
            std::cout << "<Elif List>" << std::endl;
            elif->Print(ident + 1);
            next->Print(ident);
        }

        std::unique_ptr<Stmt> elif;
        std::unique_ptr<List> next;

    };
}

#endif