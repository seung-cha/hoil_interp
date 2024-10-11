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
        FunctionCallExpr(Identifier *identifier, List *list) : identifier{identifier}, list{list}
        {

        }

        std::unique_ptr<Identifier> identifier;
        std::unique_ptr<List> list;

    };

}


#endif