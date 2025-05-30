#ifndef AST_ARR_DECL_H
#define AST_ARR_DECL_H

#include "decl.h"
#include "../expr/expr.h"
#include <memory>

namespace ASTs
{
    class ArrDecl : public Decl
    {
        public:
        ArrDecl(Identifier *identifier, Expr *index, Expr *expr, int lineNo, int charNo) : 
        Decl{nullptr, identifier, lineNo, charNo}, expr{expr}, index{index}
        {

        }

        AST *Visit(Visitor *visitor, AST *obj) override
        {
            return visitor->VisitArrDecl(this, obj);
        }

        void Print(int ident) override
        {
            PrintIdent(ident);
            std::cout << "<Array Assignment>" << std::endl;
            identifier->Print(ident + 1);
            index->Print(ident + 1);
            expr->Print(ident + 1);
        }

        std::unique_ptr<Expr> expr, index;
    };
}


#endif