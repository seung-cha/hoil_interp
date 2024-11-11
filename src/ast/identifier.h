#ifndef AST_IDENTIFIER_H
#define AST_IDENTIFIER_H

#include "terminal.h"

namespace ASTs
{
    class Identifier : public Terminal
    {
        public:
        Identifier(std::string spelling, int lineNo, int charNo) : Terminal{spelling, lineNo, charNo}
        {

        }

        AST *Visit(Visitor *visitor, AST *obj) override
        {
            return visitor->VisitIdentifier(this, obj);
        }

        void Print(int ident) override
        {
            PrintIdent(ident);
            std::cout << "[Identifier, " << spelling  << "]" << std::endl;
        }
        
    };
}

#endif