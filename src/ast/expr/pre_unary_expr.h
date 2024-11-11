#ifndef AST_PRE_UNARY_EXPR_H
#define AST_PRE_UNARY_EXPR_H 

#include "expr.h"
#include "../op/operator.h"

#include <memory>

namespace ASTs
{
    class PreUnaryExpr : public Expr
    {
        public:
        PreUnaryExpr(Expr *expr, Operator *op, int lineNo, int charNo) : expr{expr}, op{op}, Expr{lineNo, charNo}
        {

        }

        AST *Visit(Visitor *visitor, AST *obj) override
        {
            return visitor->VisitPreUnaryExpr(this, obj);
        }

        void Print(int ident) override
        {
            PrintIdent(ident);
            std::cout << "<Pre Unary Expression>" << std::endl;
            op->Print(ident + 1);
            expr->Print(ident + 1);
        }
        
        std::unique_ptr<Expr> expr;
        std::unique_ptr<Operator> op;

    };
}


#endif