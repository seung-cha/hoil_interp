#ifndef AST_ARRAY_EXPR_H
#define AST_ARRAY_EXPR_H

#include "expr.h"
#include "../identifier.h"
#include <memory>

namespace ASTs
{
    class ArrayExpr : public Expr
    {
        public:
        ArrayExpr(Identifier *identifier, Expr *index, int lineNo, int charNo) : identifier{identifier}, index{index},  Expr{lineNo, charNo}
        {
            
        }

        AST *Visit(Visitor *visitor, AST *obj) override
        {
            return visitor->VisitArrayExpr(this, obj);
        }

        void Print(int ident) override
        {
            PrintIdent(ident);
            std::cout << "<Array Expression>" << std::endl;
            identifier->Print(ident + 1);
            index->Print(ident + 1);
        }

        std::unique_ptr<Expr> index;
        std::unique_ptr<Identifier> identifier;
    };
}

#endif