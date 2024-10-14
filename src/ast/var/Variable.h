#ifndef AST_VAR_H
#define AST_VAR_H

#include "../ast.h"
#include "../identifier.h"
#include <string>
#include <memory>

namespace ASTs
{
    class Variable : public AST
    {
        public: 
        Variable(Identifier *identifier) : identifier{identifier}
        {

        }

        void Visit(Visitor *visitor) override
        {
            visitor->VisitVariable(this);
        }

        void Print(int ident) override
        {
            PrintIdent(ident);
            std::cout << "<Variable>" << std::endl;
            identifier->Print(ident + 1);
        }
        
        std::unique_ptr<Identifier> identifier;
    };
}

#endif