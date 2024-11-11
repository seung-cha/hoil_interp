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
        FuncDecl(Type *type, Identifier *identifier, List *params, Stmt *stmt, int lineNo, int charNo) : Decl{type, identifier, lineNo, charNo},
        params{params}, stmt{stmt}
        {

        }

        AST *Visit(Visitor *visitor, AST *obj) override
        {
            return visitor->VisitFuncDecl(this, this);
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

        std::unique_ptr<List> params;
        std::unique_ptr<Stmt> stmt;


    };
}


#endif