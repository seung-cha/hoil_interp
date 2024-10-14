#ifndef AST_OP_H
#define AST_OP_H

#include "../terminal.h"

namespace ASTs
{
    class Operator : public Terminal
    {
        public:
        Operator(std::string spelling) : Terminal{spelling}
        {

        }

        void Visit(Visitor *visitor) override
        {
            visitor->VisitOperator(this);
        }

        void Print(int ident) override
        {
            PrintIdent(ident);
            std::cout << "[Operator, " << spelling << "]" << std::endl;
        }

    };
}

#endif