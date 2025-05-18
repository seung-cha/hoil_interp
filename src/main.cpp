#include <iostream>
#include <cassert>
#include <string.h>
#include "compiler.h"
#include "AST.h"

int main(int argc, char** argv)
{
    if(argc <= 2)
    {
        std::cout << "Usage: " << argv[0] << " [source_file] [output_file] --flags" << std::endl;
        std::cout << "Type --help or -h for more detail." << std::endl;
        return EXIT_SUCCESS;
    }

    Compiler compiler{argv[1], argc, argv};

    // Reserve functions
    // 
    // 1. void Print(text: Sentence)
    // 2. void Say(text: Sentence)
    // 3. void OpenGripper()
    // 4. void CloseGripper()
    // 5. void MoveTo(x: Number, y: Number, z: Number)
    // 6. void MoveBy(x: Number, y: Number, z: Number)
    
    compiler.ReserveFunc(ASTs::VarType::VOID, "Print", {ASTs::VarType::STRING}, {"text"});
    compiler.ReserveFunc(ASTs::VarType::VOID, "Say", {ASTs::VarType::STRING}, {"text"});
    compiler.ReserveFunc(ASTs::VarType::VOID, "OpenGripper", {}, {});
    compiler.ReserveFunc(ASTs::VarType::VOID, "CloseGripper", {}, {});
    compiler.ReserveFunc(ASTs::VarType::VOID, "MoveTo", {ASTs::VarType::REAL, ASTs::VarType::REAL, ASTs::VarType::REAL}, {"x", "y", "z"});
    compiler.ReserveFunc(ASTs::VarType::VOID, "MoveBy", {ASTs::VarType::REAL, ASTs::VarType::REAL, ASTs::VarType::REAL}, {"x", "y", "z"});



    return compiler.Run() ? EXIT_SUCCESS : EXIT_FAILURE;
}