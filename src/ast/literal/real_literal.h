#ifndef AST_REAL_LITERAL_H
#define AST_REAL_LITERAL_H

#include "literal.h"

namespace ASTs
{
    class RealLiteral : public Literal
    {
        public:
        RealLiteral(std::string spelling) : Literal{spelling}
        {
            
        }

        void Visit(Visitor *visitor) override
        {
            visitor->VisitRealLiteral(this);
        }

        void Print(int ident) override
        {
            PrintIdent(ident);
            std::cout << "[Real Literal, " << spelling << "]" << std::endl;
        }

    };
}


#endif