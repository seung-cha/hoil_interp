#ifndef AST_BOOL_LITERAL_H
#define AST_BOOL_LITERAL_H

#include "literal.h"

namespace ASTs
{
    class BoolLiteral : public Literal
    {
        public:
        BoolLiteral(std::string spelling, int lineNo, int charNo) : Literal{spelling, lineNo, charNo}
        {
            
        }

        AST *Visit(Visitor *visitor, AST *obj) override
        {
            return visitor->VisitBoolLiteral(this, obj);
        }

        void Print(int ident) override
        {
            PrintIdent(ident);
            std::cout << "[Boolean Literal, " << spelling << "]" << std::endl;
        }

    };
}


#endif