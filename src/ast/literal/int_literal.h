#ifndef AST_INT_LITERAL_H
#define AST_INT_LITERAL_H

#include "literal.h"

namespace ASTs
{
    class IntLiteral : public Literal
    {
        public:
        IntLiteral(std::string spelling) : Literal{spelling}
        {
            
        }
    };
}


#endif