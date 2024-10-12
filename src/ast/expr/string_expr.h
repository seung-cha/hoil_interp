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

        void Print(int ident) override
        {
            PrintIdent(ident);
            std::cout << "<String Literal>" << std::endl;
            literal->Print(ident + 1); 
        }
        
        std::unique_ptr<StringLiteral> literal;
    };
}

#endif