#ifndef AST_INSTRUCT_STMT_H
#define AST_INSTRUCT_STMT_H

#include "stmt.h"
#include "../literal/string_literal.h"
#include <memory>
#include <string>

namespace ASTs
{
    class InstructStmt : public Stmt
    {
        public:
        InstructStmt(std::string value, int lineNo, int charNo) : Stmt{lineNo, charNo}, value{value}
        {
            
        }

        AST *Visit(Visitor *visitor, AST *obj) override
        {
            return visitor->VisitInstructStmt(this, obj);
        }

        void Print(int ident) override
        {
            PrintIdent(ident);
            printf("<Instruct Stmt | %s >\n", value.c_str());
        }

        std::string value;
        
    };

}

#endif