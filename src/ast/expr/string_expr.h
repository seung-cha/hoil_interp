#ifndef AST_STRING_EXPR_H
#define AST_STRING_EXPR_H

#include "expr.h"
#include "../literal/string_literal.h"
#include <memory>

namespace ASTs
{
    class StringExpr : public Expr
    {
        public:
        StringExpr(StringLiteral *literal) : literal{literal}
        {

        }

        AST *Visit(Visitor *visitor, AST *obj) override
        {
            return visitor->VisitStringExpr(this, obj);
        }

        void Print(int ident) override
        {
            PrintIdent(ident);
            std::cout << "<String Expr>" << std::endl;
            literal->Print(ident + 1); 
        }
        
        std::unique_ptr<StringLiteral> literal;
    };
}

#endif