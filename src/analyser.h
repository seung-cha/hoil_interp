#ifndef ANALYSER_H
#define ANALYSER_H

#include "symbol_table.h"
#include "ast/visitor.h"
#include "AST.h"

class Analyser : public ASTs::Visitor
{
    public:
    Analyser(ASTs::Program *program) : program{program}
    {
        VisitProgram(program);
    }

    private:
    ASTs::Program *program;
};


#endif