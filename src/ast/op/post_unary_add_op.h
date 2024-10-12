#ifndef AST_POST_UNARY_ADD_OP_H
#define AST_POST_UNARY_ADD_OP_H

#include "operator.h"

namespace ASTs
{
    class PostUnaryAddOp : public Operator
    {
        public:
        PostUnaryAddOp(std::string spelling) : Operator{spelling}
        {
            
        }
    };
}

#endif