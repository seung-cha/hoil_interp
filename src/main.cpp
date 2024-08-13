#include <iostream>
#include <cassert>
#include <string.h>
#include "scanner.h"
#include "lexer.h"
#include "lexemes.h"


int main(int argc, char** argv)
{
    if(argc <= 1)
    {
        std::cout << "Usage: " << argv[0] << " [source_file] --flags" << std::endl;
        std::cout << "Type --help or -h for more detail." << std::endl;
        return EXIT_SUCCESS;
    }

    bool lexer_verbose = false;

    for(int i = 0; i < argc; i++)
    {
        // Print help
        if(strcmp(argv[i], "--help") == 0 || strcmp(argv[i], "-h") == 0)
        {
            std::cout << "Usage: " << argv[0] << 
            " [source_file] --flags\n" 
            "--flags can be any of the following:\n\n"
            "--lexer-verbose    Print stats for lexer" << std::endl;

            return EXIT_SUCCESS;
        }

        if(strcmp(argv[i], "--lexer-verbose") == 0)
        {
            lexer_verbose = true;
        }
    }



    Scanner scanner{argv[1]};

    if(!scanner.IsReady())
    {
        std::cout << "Scanner failed to open the file. Perhaps it is invalid?" << std::endl;
        return EXIT_FAILURE;
    }


    Lexer lexer{&scanner};
    Lexicons::Lexicon* lex = nullptr;

    if(lexer_verbose)
    {
        lexer.Verbose();
    }

    return EXIT_SUCCESS;
}