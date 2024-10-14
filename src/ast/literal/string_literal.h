#ifndef AST_STRING_LITERAL_H
#define AST_STRING_LITERAL_H

#include "literal.h"

namespace ASTs
{
    class StringLiteral : public Literal
    {
        public:
        StringLiteral(std::string spelling) : Literal{spelling}
        {
            
        }

        void Visit(Visitor *visitor) override
        {
            visitor->VisitStringLiteral(this);
        }

        void Print(int ident) override
        {
            PrintIdent(ident);
            std::cout << "[String Literal, " << spelling << "]" << std::endl;
        }

    };
}


#endif