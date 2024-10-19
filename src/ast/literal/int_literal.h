#ifndef AST_INT_LITERAL_H
#define AST_INT_LITERAL_H

#include "literal.h"

namespace ASTs
{
    class IntLiteral : public Literal
    {
        public:
        IntLiteral(std::string spelling) : Literal{spelling}
        {
            
        }

        AST *Visit(Visitor *visitor, AST *obj) override
        {
            return visitor->VisitIntLiteral(this, obj);
        }

        void Print(int ident) override
        {
            PrintIdent(ident);
            std::cout << "[Integer Literal, " << spelling << "]" << std::endl;
        }

    };
}


#endif