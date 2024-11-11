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
            lineNo = literal->lineNo;
            charNo = literal->charNo;
        }

        AST *Visit(Visitor *visitor, AST *obj) override
        {
            return visitor->VisitIntExpr(this, obj);
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