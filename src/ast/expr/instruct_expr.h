#ifndef AST_INSTRUCT_EXPR
#define AST_INSTRUCT_EXPR

#include "expr.h"
#include "../../lexicon/misc/instruct.h"
#include <memory>
#include <string>

namespace ASTs
{
    class InstructExpr : public Expr
    {
        public:
        std::string value;
        InstructType type;
        InstructExpr(InstructType type, std::string value) : value{value}, type{type}
        {
            isInstruct = true;
        }

        AST *Visit(Visitor *visitor, AST *obj) override
        {
            visitor->VisitInstructExpr(this, nullptr);
            return nullptr;
        }

        void Print(int ident) override
        {
            PrintIdent(ident);
            printf("<Instruct Expr | %s >\n", value.c_str());
        }
    };

}

#endif