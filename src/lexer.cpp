#include "lexer.h"
#include <cctype>
#include <sstream>
#include <iostream>
#include "include/openai/openai.hpp"

using json = nlohmann::json;

Lexer::Lexer(Scanner *scanner) : scanner{scanner}
{
    // Set the chain
    componentHead = &alphaComp;
    componentHead->Chain(&numComp)->Chain(&strComp)->Chain(&miscComp);

    // Collect lexemes
    while(scanner->IsReady())
    {
        auto lex = componentHead->GetLexicon(scanner);
        assert(lex && "Lexer received nullptr\n");

        if(lex->Id == Lexicons::Lexicon::INSTRUCT)
        {
            instructLexemes.push_back(static_cast<Lexicons::Instruct*>(lex));
        }
        
        lexemes.push_back(lex);
    }

    // To do: assign tag to each instruct stmt
    if(instructLexemes.empty()) return;
    
    // Print json file to dispatch
    json req;
    req["model"] = "o4-mini-2025-04-16";
    
    
    json msgs;
    msgs[0] = {
        { "role", "system" },
        { "content", R"(Given a Json file, your task is to identify intention and classify each object.
            The json file contains sentences, whose intention can be "conditional", "loop", "assignment", "expression" or "misc".
            For example, a sentence like "If X is true" is conditional, whereas "While X is less than 7" is loop.
            For all sentences that are ambiguous or can be interpreted in more than one way, or no suitable classification exists, you need to classify them as misc.
            For example, "If x is 2 then x is 5" is misc because it is both conditional and assignment.
            Note that loop may appear conditional too but is considered valid.
            Your output should consist of Json array where ith object is a string that is one of the four classification for the ith input.)"}
        };
        
        
        json instructs;
        for(int i = 0; i < instructLexemes.size(); i++)
        {
            instructs[i] = instructLexemes[i]->value;
        }
        
        msgs[1] = {
            { "role", "user" },
            { "content",  instructs.dump()},
        };
        
        req["messages"] = msgs;
        
        
    openai::start();
    auto response = openai::chat().create(req);

    auto res = response["choices"][0]["message"]["content"];
    std::cout << "res: " << res << std::endl;

   
    


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