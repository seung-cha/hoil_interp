#include "lexer.h"
#include <cctype>
#include <sstream>
#include <iostream>

Lexer::Lexer(Scanner *scanner) : scanner{scanner}
{
    // Set the chain
    componentHead = &alphaComp;
    componentHead->Chain(&numComp)->Chain(&strComp)->Chain(&miscComp);

    // Collect lexemes
    while(scanner->IsReady())
    {
        lexemes.push_back(componentHead->GetLexicon(scanner));
    }
}

Lexer::~Lexer()
{
    for(const auto& token : lexemes)
    {
        delete token;
    }
}


Lexicons::Lexicon *Lexer::GetLexicon()
{
    if(ctr >= lexemes.size())
    {
        return nullptr;
    }

    return lexemes[ctr++];
}

void Lexer::Verbose() const
{
    int err = 0;
    int id = 0;
    for(const auto& token : lexemes)
    {
        if(token->Id == Lexicons::Lexicon::ERR)
        {
            err++;
        }
        else if(token->Id == Lexicons::Lexicon::IDENTIFIER)
        {
            id++;
        }

        std::cout << token->Verbose() << std::endl;
    }

    std::cout << "Tokens: " << lexemes.size() << std::endl;
    std::cout << "IDs: " << id << std::endl;
    std::cout << "Errors: " << err << std::endl;
}