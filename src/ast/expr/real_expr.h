#ifndef AST_REAL_EXPR_H
#define AST_REAL_EXPR_H

#include "expr.h"
#include "../literal/real_literal.h"
#include <memory>

namespace ASTs
{
    class RealExpr : public Expr
    {
        public:
        RealExpr(RealLiteral *literal) : literal{literal}
        {
            lineNo = literal->lineNo;
            charNo = literal->charNo;
        }

        AST *Visit(Visitor *visitor, AST *obj) override
        {
            return visitor->VisitRealExpr(this, obj);
        }

        void Print(int ident) override
        {
            PrintIdent(ident);
            std::cout << "<Real Expression>" << std::endl;
            literal->Print(ident + 1);
        }
        
        std::unique_ptr<RealLiteral> literal;
    };
}

#endif