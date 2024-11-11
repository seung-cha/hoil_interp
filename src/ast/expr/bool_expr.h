#ifndef AST_BOOL_EXPR_H
#define AST_BOOL_EXPR_H

#include "expr.h"
#include "../literal/bool_literal.h"
#include <memory>

namespace ASTs
{
    class BoolExpr : public Expr
    {
        public:
        BoolExpr(BoolLiteral *literal) : literal{literal}
        {
            lineNo = literal->lineNo;
            charNo = literal->charNo;
        }

        AST *Visit(Visitor *visitor, AST *obj) override
        {
            return visitor->VisitBoolExpr(this, obj);
        }

        void Print(int ident) override
        {
            PrintIdent(ident);
            std::cout << "<Boolean Expression>" << std::endl;
            literal->Print(ident + 1);
        }
        
        std::unique_ptr<BoolLiteral> literal;
    };
}

#endif