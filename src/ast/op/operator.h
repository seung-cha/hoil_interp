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

    };
}

#endif