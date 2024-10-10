#ifndef AST_PRE_UNARY_ADD_OP_H
#define AST_PRE_UNARY_ADD_OP_H

#include "operator.h"

namespace ASTs
{
    class PreUnaryAddOp : public Operator
    {
        public:
        PreUnaryAddOp(std::string spelling) : Operator{spelling}
        {
            
        }
    };
}

#endif