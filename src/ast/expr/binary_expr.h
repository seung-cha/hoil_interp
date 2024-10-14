#ifndef AST_BINARY_EXPR_H
#define AST_BINARY_EXPR_H

#include "expr.h"
#include "../op/operator.h"
#include <memory>

namespace ASTs
{
    class BinaryExpr : public Expr
    {
        public:
        BinaryExpr(Expr *lhs, Expr *rhs, Operator *op) : lhs{lhs}, rhs{rhs}, op{op}
        {

        }

        void Visit(Visitor *visitor) override
        {
            visitor->VisitBinaryExpr(this);
        }
        
        void Print(int ident) override
        {
            PrintIdent(ident);
            std::cout << "<Binary Expression>" << std::endl;
            lhs->Print(ident + 1);
            op->Print(ident + 1);
            rhs->Print(ident + 1);
        }
        
        std::unique_ptr<Expr> lhs, rhs;
        std::unique_ptr<Operator> op;
    };

}

#endif