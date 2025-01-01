#ifndef AST_CALL_STMT_H
#define AST_CALL_STMT_H

#include "stmt.h"
#include "../identifier.h"
#include "../list/list.h"
#include <memory>

namespace ASTs
{
    class CallStmt : public Stmt
    {
        public:
        CallStmt(ASTs::Identifier *identifier, ASTs::List *args, int lineNo, int charNo) : Stmt{lineNo, charNo}, identifier{identifier}, args{args}
        {
            
        }

        AST *Visit(Visitor *visitor, AST *obj) override
        {
            return visitor->VisitCallStmt(this, obj);
        }

        void Print(int ident) override
        {
            PrintIdent(ident);
            std::cout << "<Call Stmt>" << std::endl;
            identifier->Print(ident + 1);
            args->Print(ident + 1);
        }

        std::unique_ptr<ASTs::Identifier> identifier;
        std::unique_ptr<ASTs::List> args;

        
    };

}

#endif