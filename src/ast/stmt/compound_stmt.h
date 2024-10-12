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

        std::unique_ptr<List> list;
    };

}

#endif