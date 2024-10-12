#ifndef AST_MOD_OP_H
#define AST_MOD_OP_H

#include "operator.h"

namespace ASTs
{
    class ModOp : public Operator
    {
        public:
        ModOp(std::string spelling) : Operator{spelling}
        {
            
        }
    };
}

#endif