#ifndef AST_TERMINAL_H
#define AST_TERMINAL_H

#include "ast.h"
#include <string>

namespace ASTs
{
    class Terminal : public AST
    {
        public:
        Terminal(std::string spelling) : spelling{spelling}
        {

        }

        std::string spelling;

    };
}

#endif