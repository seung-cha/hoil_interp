#ifndef AST_IDENTIFIER_H
#define AST_IDENTIFIER_H

#include "terminal.h"

namespace ASTs
{
    class Identifier : public Terminal
    {
        public:
        Identifier(std::string spelling) : Terminal{spelling}
        {

        }

        void Visit(Visitor *visitor) override
        {
            visitor->VisitIdentifier(this);
        }

        void Print(int ident) override
        {
            PrintIdent(ident);
            std::cout << "[Identifier, " << spelling  << "]" << std::endl;
        }
        
    };
}

#endif