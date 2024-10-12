#ifndef AST_PROGRAM_H
#define AST_PROGRAM_H

#include "ast.h"
#include "list/list.h"
#include <memory>

namespace ASTs
{
    class Program : public AST
    {
        public:
        Program(List *list) : list{list}
        {

        }

        std::unique_ptr<List> list;

    };
}

#endif