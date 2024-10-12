#ifndef AST_ASSIGN_OP_H
#define AST_ASSIGN_OP_H

#include "operator.h"

namespace ASTs
{
    class AssignOp : public Operator
    {
        public:
        AssignOp(std::string spelling) : Operator{spelling}
        {
            
        }
    };
}

#endif