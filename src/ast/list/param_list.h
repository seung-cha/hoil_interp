#ifndef AST_PARAM_LIST_H
#define AST_PARAM_LIST_H

#include "../decl/param.h"
#include "list.h"
#include <memory>

namespace ASTs
{
    class ParamList : public List
    {
        public:
        ParamList(Param *param, List *next) : param{param}, next{next} 
        {

        }

        void Visit(Visitor *visitor) override
        {
            visitor->VisitParamList(this);
        }

        void Print(int ident) override
        {
            PrintIdent(ident);
            std::cout << "<Param List>" << std::endl;
            param->Print(ident + 1);
            next->Print(ident);
        }
        
        std::unique_ptr<Param> param;
        std::unique_ptr<List> next;

    };
}

#endif