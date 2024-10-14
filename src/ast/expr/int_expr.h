#ifndef AST_INT_EXPR_H
#define AST_INT_EXPR_H

#include "expr.h"
#include "../literal/int_literal.h"
#include <memory>

namespace ASTs
{
    class IntExpr : public Expr
    {
        public:
        IntExpr(IntLiteral *literal) : literal{literal}
        {

        }

        void Visit(Visitor *visitor) override
        {
            visitor->VisitIntExpr(this);
        }

        void Print(int ident) override
        {
            PrintIdent(ident);
            std::cout << "<Integer Expression>" << std::endl;
            literal->Print(ident + 1);
        }

        std::unique_ptr<IntLiteral> literal;
    };
}

#endif