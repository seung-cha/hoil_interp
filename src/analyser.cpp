#include "analyser.h"

using namespace ASTs;

Analyser::Analyser(Program *program) : program{program}
    {
        symbolTable.OpenScope();
        program->Visit(this);
        symbolTable.CloseScope();

        if(symbolTable.level != -1)
        {
            std::cout << "Symbol Table level is not -1 after termination?" << std::endl;
            std::cout << "Level: " << symbolTable.level << std::endl;
        }
    }