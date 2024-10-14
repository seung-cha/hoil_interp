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

        void Visit(Visitor *visitor) override
        {
            visitor->VisitFuncDecl(this);
        }

        void inline Print(int ident) override
        {
            PrintIdent(ident);
            std::cout << "<Function Declaration>" << std::endl;
            type->Print(ident + 1);
            identifier->Print(ident + 1);
            params->Print(ident + 1);
            stmt->Print(ident + 1);

        }

        std::unique_ptr<Type> type;
        std::unique_ptr<Identifier> identifier;
        std::unique_ptr<List> params;
        std::unique_ptr<Stmt> stmt;


    };
}


#endif