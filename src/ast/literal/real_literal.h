#ifndef AST_REAL_LITERAL_H
#define AST_REAL_LITERAL_H

#include "literal.h"

namespace ASTs
{
    class RealLiteral : public Literal
    {
        public:
        RealLiteral(std::string spelling) : Literal{spelling}
        {
            
        }
    };
}


#endif