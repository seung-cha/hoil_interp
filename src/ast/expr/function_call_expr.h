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
        FunctionCallExpr(Identifier *identifier, List *args, int lineNo, int charNo) : identifier{identifier}, args{args}, Expr{lineNo, charNo}
        {

        }

        AST *Visit(Visitor *visitor, AST *obj) override
        {
            return visitor->VisitFuncCallExpr(this, obj);
        }
        
        void Print(int ident) override
        {
            PrintIdent(ident);
            std::cout << "<Function Call Expression>" << std::endl;
            identifier->Print(ident + 1);
            args->Print(ident + 1);
        }

        std::unique_ptr<Identifier> identifier;
        std::unique_ptr<List> args;

    };

}


#endif