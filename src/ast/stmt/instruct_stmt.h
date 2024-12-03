#ifndef AST_INSTRUCT_STMT_H
#define AST_INSTRUCT_STMT_H

#include "stmt.h"
#include "../literal/string_literal.h"
#include <memory>

namespace ASTs
{
    class InstructStmt : public Stmt
    {
        public:
        InstructStmt(StringLiteral *literal, int lineNo, int charNo) : Stmt{lineNo, charNo}, literal{literal}
        {
            
        }

        AST *Visit(Visitor *visitor, AST *obj) override
        {
            return visitor->VisitInstructStmt(this, obj);
        }

        void Print(int ident) override
        {
            PrintIdent(ident);
            std::cout << "<Instruct Stmt>" << std::endl;
            literal->Print(ident + 1);
        }

        std::unique_ptr<StringLiteral> literal;
        
    };

}

#endif