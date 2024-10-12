#ifndef AST_PARAM_LIST_H
#define AST_PARAM_LIST_H

#include "param.h"
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
        
        std::unique_ptr<Param> param;
        std::unique_ptr<List> next;

    };
}

#endif