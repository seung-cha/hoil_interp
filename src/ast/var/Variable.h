#ifndef AST_VAR_H
#define AST_VAR_H

#include "../ast.h"
#include "../identifier.h"
#include <string>
#include <memory>

namespace ASTs
{
    class Variable : public AST
    {
        public: 
        Variable(Identifier *identifier) : identifier{identifier}
        {

        }
        
        std::unique_ptr<Identifier> identifier;
    };
}

#endif