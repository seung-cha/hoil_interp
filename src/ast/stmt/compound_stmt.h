#ifndef AST_COMPOUND_STMT_H
#define AST_COMPOUND_STMT_H

#include "stmt.h"
#include "../list/list.h"
#include <memory>

namespace ASTs
{
    class CompoundStmt : public Stmt
    {
        public:
        CompoundStmt(List *list) : list{list}
        {

        }

        AST *Visit(Visitor *visitor, AST *obj) override
        {
            return visitor->VisitCompoundStmt(this, obj);
        }

        void Print(int ident) override
        {
            PrintIdent(ident);
            std::cout << "<Compound Stmt>" << std::endl;
            list->Print(ident + 1);
        }

        std::unique_ptr<List> list;
    };

}

#endif