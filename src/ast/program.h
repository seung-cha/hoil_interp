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
        Program(List *list, int lineNo, int charNo) : list{list}, AST{lineNo, charNo}
        {

        }

        AST *Visit(Visitor *visitor, AST *obj) override
        {
            return visitor->VisitProgram(this, obj);
        }
        
        void Print(int ident) override
        {
            PrintIdent(ident);
            std::cout << "<Program>" << std::endl;
            list->Print(ident + 1);
        }

        std::unique_ptr<List> list;

    };
}

#endif