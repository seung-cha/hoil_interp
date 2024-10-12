#ifndef AST_ADD_OP_H
#define AST_ADD_OP_H

#include "operator.h"

namespace ASTs
{
    class AddOp : public Operator
    {
        public:
        AddOp(std::string spelling) : Operator{spelling}
        {
            
        }
    };
}

#endif