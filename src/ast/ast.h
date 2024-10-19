#ifndef AST_BASE_H
#define AST_BASE_H

#include <string>
#include <iostream>
#include "visitor.h"

namespace ASTs
{
    class AST
    {
        public:
        virtual void Print(int indent) = 0;
        virtual AST *Visit(Visitor *visitor, AST *obj) = 0;

        protected:
        void inline PrintIdent(int ident)
        {
            for(int i = 0; i < ident; i++)
            {
                std::cout << '\t';
            }
        }
    };

}

#endif