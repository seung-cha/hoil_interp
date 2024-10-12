#ifndef AST_SUB_OP_H
#define AST_SUB_OP_H

#include "operator.h"

namespace ASTs
{
    class SubOp : public Operator
    {
        public:
        SubOp(std::string spelling) : Operator{spelling}
        {
            
        }
    };
}

#endif