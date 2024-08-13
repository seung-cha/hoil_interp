#include "scanner.h"
#include "lexer.h"
#include "lexemes.h"
#include <iostream>
#include <cassert>


int main(int argc, char** argv)
{
    if(argc <= 1)
    {
        std::cout << "Usage: " << argv[0] << " source_file" << std::endl;
        return EXIT_SUCCESS;
    }

    Scanner scanner{argv[1]};

    if(!scanner.IsReady())
    {
        std::cout << "Scanner failed to open the file. Perhaps it is invalid?" << std::endl;
        return EXIT_FAILURE;
    }

    Lexer lexer{&scanner};

    Lexicons::Lexicon* lex = nullptr;

    while(true)
    {
        lex = lexer.GetLexicon();

        if(lex == nullptr)
        {
            break;
        }

        std::cout << lex->Verbose() << std::endl;
        delete lex;
    }


    return EXIT_SUCCESS;
}