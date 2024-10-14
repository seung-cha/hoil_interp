#ifndef AST_BOOL_LITERAL_H
#define AST_BOOL_LITERAL_H

#include "literal.h"

namespace ASTs
{
    class BoolLiteral : public Literal
    {
        public:
        BoolLiteral(std::string spelling) : Literal{spelling}
        {
            
        }

        void Visit(Visitor *visitor) override
        {
            visitor->VisitBoolLiteral(this);
        }

        void Print(int ident) override
        {
            PrintIdent(ident);
            std::cout << "[Boolean Literal, " << spelling << "]" << std::endl;
        }

    };
}


#endif