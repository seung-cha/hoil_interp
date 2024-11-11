#ifndef AST_ARG_H
#define AST_ARG_H

#include "../ast.h"
#include "../expr/expr.h"
#include <memory>

namespace ASTs
{
    class Arg : public AST
    {
        public:
        Arg(Expr *expr, int lineNo, int charNo) : expr{expr}, AST{lineNo, charNo}
        {

        }

        AST *Visit(Visitor *visitor, AST *obj) override
        {
            return visitor->VisitArg(this, obj);
        }

        void Print(int ident) override
        {
            PrintIdent(ident);
            std::cout << "<Arg>" << std::endl;
            expr->Print(ident + 1);
        }

        std::unique_ptr<Expr> expr;


    };
}

#endif