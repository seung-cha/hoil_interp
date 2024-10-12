#ifndef AST_FUNC_DECL_H
#define AST_FUNC_DECL_H

#include "decl.h"
#include "../type/type.h"
#include "../identifier.h"
#include "../list/list.h"
#include "../stmt/stmt.h"
#include <memory>


namespace ASTs
{
    class FuncDecl : public Decl
    {
        public:
        FuncDecl(Type *type, Identifier *identifier, List *params, Stmt *stmt) : type{type}, identifier{identifier},
        params{params}, stmt{stmt}
        {

        }

        std::unique_ptr<Type> type;
        std::unique_ptr<Identifier> identifier;
        std::unique_ptr<List> params;
        std::unique_ptr<Stmt> stmt;


    };
}


#endif