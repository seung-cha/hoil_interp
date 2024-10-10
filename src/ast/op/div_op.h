#ifndef AST_DIV_OP_H
#define AST_DIV_OP_H

#include "operator.h"

namespace ASTs
{
    class DivOp : public Operator
    {
        public:
        DivOp(std::string spelling) : Operator{spelling}
        {
            
        }
    };
}

#endif