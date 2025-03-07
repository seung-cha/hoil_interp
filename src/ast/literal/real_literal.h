#ifndef AST_REAL_LITERAL_H
#define AST_REAL_LITERAL_H

#include "literal.h"

namespace ASTs
{
    class RealLiteral : public Literal
    {
        public:
        RealLiteral(std::string spelling, int lineNo, int charNo) : Literal{spelling, lineNo, charNo}
        {
            
        }

        AST *Visit(Visitor *visitor, AST *obj) override
        {
            return visitor->VisitRealLiteral(this, obj);
        }

        void Print(int ident) override
        {
            PrintIdent(ident);
            std::cout << "[Real Literal, " << spelling << "]" << std::endl;
        }

    };
}


#endif