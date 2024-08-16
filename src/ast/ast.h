#ifndef AST_BASE_H
#define AST_BASE_H

#include <string>

namespace ASTs
{
    class AST
    {
        public:
        virtual std::string const ToString() const = 0;
    };

}

#endif