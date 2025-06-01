#include <iostream>
#include <cassert>
#include <string.h>
#include "compiler.h"
#include "AST.h"

typedef ASTs::VarType Type;

int main(int argc, char** argv)
{
    if(argc <= 2)
    {
        std::cout << "Usage: " << argv[0] << " [source_file] [output_file] --flags" << std::endl;
        std::cout << "Type --help or -h for more detail." << std::endl;
        return EXIT_SUCCESS;
    }

    // TODO: Newline token is not generated after instruct token. Generate it
    Compiler compiler{argv[1], argc, argv};

    // Reserve functions
    // 
    // 1. void Print(text: Sentence)
    // 2. void Say(text: Sentence)
    // 3. void OpenGripper()
    // 4. void CloseGripper()
    // 5. void MoveTo(x: Number, y: Number, z: Number)
    // 6. void MoveBy(x: Number, y: Number, z: Number)
    //
    // Manipulation-Related functions
    //
    // 1. void Grab(obj: Object)     # close the gripper and grab object; internally calls MoveGroupCommander.attach_object()
    // 2. void Release()             # Open the gripper. Internally calls MoveGroupCommander.detach_object()
    // 3. Array PositionOf(obj: Object) #  array of size 3 (0 ~ 2), corresponding to the x, y, z coordinate of the object.

    // EXAMPLE-SPECIFIC-FUNCTIONS
    // 1. Number HeightOf(obj: Object) # Get the height of the object (stick)

    compiler.ReserveFunc(Type::VOID, "Print", {Type::STRING}, {"text"});
    compiler.ReserveFunc(Type::VOID, "Say", {Type::STRING}, {"text"});
    compiler.ReserveFunc(Type::VOID, "OpenGripper", {}, {});
    compiler.ReserveFunc(Type::VOID, "CloseGripper", {}, {});
    compiler.ReserveFunc(Type::VOID, "MoveTo", {Type::REAL, Type::REAL, Type::REAL}, {"x", "y", "z"});
    compiler.ReserveFunc(Type::VOID, "MoveBy", {Type::REAL, Type::REAL, Type::REAL}, {"x", "y", "z"});

    // Manipulation-related functions
    compiler.ReserveFunc(Type::VOID, "Grab", {Type::OBJECT}, {"obj"});
    compiler.ReserveFunc(Type::VOID, "Release", {}, {});
    compiler.ReserveFunc(Type::ARRAY, "PositionOf", {Type::OBJECT}, {"obj"});

    // Example-specific functions
    compiler.ReserveFunc(Type::REAL, "HeightOf", {Type::OBJECT}, {"obj"});



    return compiler.Run() ? EXIT_SUCCESS : EXIT_FAILURE;
}