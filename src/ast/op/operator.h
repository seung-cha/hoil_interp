#ifndef AST_OP_H
#define AST_OP_H

#include <cassert>
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

        /// @brief Check if the two operands are compatible with this operator (binary)
        /// @param type1 
        /// @param type2 
        /// @return 
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
                return type1->Compatible(type2) && ((type1->IsIntType() || type1->IsRealType() || type1->IsErrorType()));
            }
            else if(spelling == "%")
            {
                return (type1->IsIntType() && type2->IsIntType()) || (type1->IsErrorType() || type2->IsErrorType());
            }
            else
            {
                fprintf(stderr, "%s", spelling.c_str());
                assert(false && "Binary operator could not resolve this type!\n");
            }
        }


        /// @brief Check if the operand is compatible with this operator (unary)
        /// @param type 
        /// @return 
        bool Compatible(Type *type)
        {
            if(spelling == "!")
            {
                return type->IsBoolType() || type->IsErrorType();
            }
            else
            {
                // unary numeric operators
                return type->IsRealType() || type->IsIntType() || type->IsErrorType();
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