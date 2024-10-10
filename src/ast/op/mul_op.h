#ifndef AST_MUL_OP_H
#define AST_MUL_OP_H

#include "operator.h"

namespace ASTs
{
    class MulOp : public Operator
    {
        public:
        MulOp(std::string spelling) : Operator{spelling}
        {
            
        }
    };
}

#endif