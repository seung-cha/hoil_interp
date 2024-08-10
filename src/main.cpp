#include "scanner.h"
#include <iostream>

int main(int argc, char** argv)
{
    if(argc != 2)
    {
        std::cout << "Usage: " << argv[0] << " source_file" << std::endl;
        return EXIT_FAILURE;
    }

    Scanner scanner{argv[1]};

    if(!scanner.IsReady())
    {
        std::cout << "Scanner failed to open the file. Perhaps it is invalid?" << std::endl;
    }


    return EXIT_SUCCESS;
}