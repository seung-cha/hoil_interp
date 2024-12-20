#ifndef AST_VAR_EXPR_H
#define AST_VAR_EXPR_H

#include "expr.h"
#include "../var/Variable.h"
#include <memory>

namespace ASTs
{
    class VariableExpr : public Expr
    {
        public:
        VariableExpr(Variable *variable) : variable{variable}
        {
            lineNo = variable->lineNo;
            charNo = variable->charNo;
        }

        AST *Visit(Visitor *visitor, AST *obj) override
        {
            return visitor->VisitVarExpr(this, obj);
        }

        void Print(int ident) override
        {
            PrintIdent(ident);
            std::cout << "<Variable Expression>" << std::endl;
            type->Print(ident + 1);
            variable->Print(ident + 1);
        }

        std::unique_ptr<Variable> variable;
    };

}

#endif