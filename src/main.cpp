#include <iostream>
#include <cassert>
#include <string.h>
#include "compiler.h"
#include "AST.h"

int main(int argc, char** argv)
{
    if(argc <= 1)
    {
        std::cout << "Usage: " << argv[0] << " [source_file] --flags" << std::endl;
        std::cout << "Type --help or -h for more detail." << std::endl;
        return EXIT_SUCCESS;
    }

    Compiler compiler{argv[1], argc, argv};
    return compiler.Run() ? EXIT_SUCCESS : EXIT_FAILURE;
}