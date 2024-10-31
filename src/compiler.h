#ifndef COMPILER_H
#define COMPILER_H

#include <memory>
#include <vector>
#include <string>

#include "ast/type/type.h"
#include "ast/decl/func_decl.h"


class Compiler
{
    public:
    Compiler(char *source, int argc, char **argv) : source{source}, argc{argc}, argv{argv}
    {

    }

    bool Run();
    void ReserveFunc(ASTs::VarType type, std::string decl, std::vector<ASTs::VarType> params, std::vector<std::string> paramIdent);

    private:
    /**
     * Reserve a function to be used
     */
    std::vector<std::unique_ptr<ASTs::FuncDecl>> reservedFuncs;
    ASTs::Type *MakeType(ASTs::VarType type);
    char *source;
    int argc;
    char **argv;



};




#endif