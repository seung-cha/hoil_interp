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
        ERROR,
        OBJECT,
        ATTRIBUTE,
    };

    class Type : public AST
    {
        public:
        Type(enum VarType type, int lineNo, int charNo) : dataType{type}, AST{lineNo, charNo}
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

        bool inline IsAttributeType()
        {
            return dataType == VarType::ATTRIBUTE;
        }

        bool inline IsObjectType()
        {
            return dataType == VarType::OBJECT;
        }

        /**
         * Return a deep copy of this object.
         */
        virtual std::unique_ptr<Type> DeepCopy() = 0;
        virtual bool Compatible(Type *type) = 0;
        

        protected:
        enum VarType dataType;
    };
}

#endif