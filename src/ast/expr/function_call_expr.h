#ifndef AST_FUNC_CALL_EXPR
#define AST_FUNC_CALL_EXPR

#include "expr.h"
#include "../list/list.h"
#include "../identifier.h"
#include <memory>
namespace ASTs
{
    class FunctionCallExpr : public Expr
    {
        public:
        FunctionCallExpr(Identifier *identifier, List *params) : identifier{identifier}, params{params}
        {

        }
        
        void Print(int ident) override
        {
            PrintIdent(ident);
            std::cout << "<Function Call Expression>" << std::endl;
            identifier->Print(ident + 1);
            params->Print(ident + 1);
        }

        std::unique_ptr<Identifier> identifier;
        std::unique_ptr<List> params;

    };

}


#endif