#ifndef AST_TYPE_H
#define AST_TYPE_H

#include "../ast.h"

namespace ASTs
{

    enum VarType
    {
        INT,
        REAL,
        BOOL,
        STRING,
        VOID,
        ERROR
    };

    class Type : public AST
    {
        public:
        Type(enum VarType type) : type{type}
        {

        }
        
        bool inline IsIntType()
        {
            return type == VarType::INT;
        }

        bool inline IsRealType()
        {
            return type == VarType::REAL;
        }

        bool inline IsBoolType()
        {
            return type == VarType::BOOL;
        }

        bool inline IsStringType()
        {
            return type == VarType::STRING;
        }

        bool inline IsVoidType()
        {
            return type == VarType::VOID;
        }

        bool inline IsErrorType()
        {
            return type == VarType::ERROR;
        }

        protected:
        enum VarType type;

    };
}

#endif