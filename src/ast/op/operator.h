#ifndef AST_OP_H
#define AST_OP_H

#include "../terminal.h"
#include "../type/type.h"

namespace ASTs
{
    class Operator : public Terminal
    {
        public:
        Operator(std::string spelling, int lineNo, int charNo) : Terminal{spelling, lineNo, charNo}
        {
            if(spelling == "==" || spelling == "!=" ||
            spelling == "<=" || spelling == ">=" || 
            spelling == "<" || spelling == ">" ||
            spelling == "!" || spelling == "&&" || spelling == "||")
            {
                boolOp = true;
            }
        }

        Operator(std::string spelling) : Terminal{spelling, 0, 0}
        {

        }

        AST *Visit(Visitor *visitor, AST *obj) override
        {
            return visitor->VisitOperator(this, obj);
        }

        void Print(int ident) override
        {
            PrintIdent(ident);
            std::cout << "[Operator, " << spelling << "]" << std::endl;
        }

        bool Compatible(Type *type1, Type *type2)
        {

            if(spelling == "=" || spelling == "==" || spelling == "!=")
            {
                return type1->Compatible(type2);
            }
            else if(spelling == "||" || spelling == "&&")
            {
                return type1->Compatible(type2) && (type1->IsBoolType() || type1->IsAttributeType() || type1->IsStringType());
            }
            else if(spelling == "+" || spelling == "-" || spelling == "*" || spelling == "/" ||
            spelling == "<"  || spelling == ">" || spelling == "<=" || spelling == ">=" || spelling == "-=" ||
            spelling == "+=" || spelling == "/=" || spelling == "*=")
            {
                return type1->Compatible(type2) && (type1->IsIntType() || type1->IsRealType());
            }
            else if(spelling == "%")
            {
                return (type1->IsIntType() && type2->IsIntType()) || (type1->IsErrorType() || type2->IsErrorType());
            }
            else if(spelling == "!")
            {
                return type1->IsBoolType() || type1->IsErrorType();
            }
            else
            {
                // unary add, sub ops left
                return type1->IsRealType() || type1->IsIntType() || type1->IsErrorType();
            }
        }

        bool IsBoolOp()
        {
            return boolOp;
        }

        private:
        bool boolOp = false;

    };
}

#endif