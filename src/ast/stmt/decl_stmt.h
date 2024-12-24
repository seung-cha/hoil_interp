#ifndef AST_DECL_STMT_H
#define AST_DECL_STMT_H

#include "stmt.h"
#include "../decl/decl.h"
#include<memory>

namespace ASTs
{
    class DeclStmt : public Stmt
    {
        public:
        DeclStmt(Decl *decl, int lineNo, int charNo) : decl{decl}, Stmt{lineNo, charNo}
        {

        }
        
        AST *Visit(Visitor *visitor, AST *obj) override
        {
            return visitor->VisitDeclStmt(this, obj);
        }

        void Print(int ident) override
        {
            PrintIdent(ident);
            std::cout << "<Decl Stmt>" << std::endl;
            decl->Print(ident + 1);
        }

        std::unique_ptr<Decl> decl;
    };
}


#endif