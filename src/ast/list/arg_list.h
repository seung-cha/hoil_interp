#ifndef AST_ARG_LIST_H
#define AST_ARG_LIST_H

#include "list.h"
#include "arg.h"
#include <memory>

namespace ASTs
{
    class ArgList : public List
    {
        public:
        ArgList(Arg *arg, List *next) : arg{arg}, next{next}
        {

        }

        void Visit(Visitor *visitor) override
        {
            visitor->VisitArgList(this);
        }

        void Print(int ident) override
        {
            PrintIdent(ident);
            std::cout << "<Arg List>" << std::endl;
            arg->Print(ident + 1);
            next->Print(ident);
        }
        
        std::unique_ptr<Arg> arg;
        std::unique_ptr<List> next;
        

    };
}

#endif