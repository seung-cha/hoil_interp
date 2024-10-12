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