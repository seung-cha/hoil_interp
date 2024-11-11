#ifndef AST_DECL_H
#define AST_DECL_H

#include "../ast.h"
#include <memory>
#include "../type/type.h"
#include "../identifier.h"

namespace ASTs
{
    class Decl : public AST
    {
        public:
        Decl(Type *type, Identifier *identifier, int lineNo, int charNo) : type{type}, identifier{identifier}, AST{lineNo, charNo}
        {

        }

        std::unique_ptr<Type> type;
        std::unique_ptr<Identifier> identifier;
        bool isFuncDecl = false;
        bool isParamDecl = false;
        bool isVarDecl = false;
    };
}


#endif