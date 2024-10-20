#ifndef AST_TYPE_H
#define AST_TYPE_H

#include "../ast.h"
#include <memory>

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
        Type(enum VarType type) : dataType{type}
        {

        }
        
        bool inline IsIntType()
        {
            return dataType == VarType::INT;
        }

        bool inline IsRealType()
        {
            return dataType == VarType::REAL;
        }

        bool inline IsBoolType()
        {
            return dataType == VarType::BOOL;
        }

        bool inline IsStringType()
        {
            return dataType == VarType::STRING;
        }

        bool inline IsVoidType()
        {
            return dataType == VarType::VOID;
        }

        bool inline IsErrorType()
        {
            return dataType == VarType::ERROR;
        }

        /**
         * Return a deep copy of this object.
         */
        virtual std::unique_ptr<Type> DeepCopy() = 0;
        

        protected:
        enum VarType dataType;

    };
}

#endif