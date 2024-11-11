#ifndef AST_TERMINAL_H
#define AST_TERMINAL_H

#include "ast.h"
#include <string>

namespace ASTs
{
    class Terminal : public AST
    {
        public:
        Terminal(std::string spelling, int lineNo, int charNo) : spelling{spelling}, AST{lineNo, charNo}
        {

        }

        std::string spelling;

    };
}

#endif