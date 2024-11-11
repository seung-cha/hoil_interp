#ifndef AST_LITERAL_H
#define AST_LITERAL_H

#include "../terminal.h"

namespace ASTs
{
    class Literal : public Terminal
    {
        public:
        Literal(std::string spelling, int lineNo, int charNo) : Terminal{spelling, lineNo, charNo}
        {
            
        }
    };
}


#endif