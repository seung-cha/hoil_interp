#include "lexer.h"
#include <cctype>
#include <sstream>

Lexer::Lexer(Scanner *scanner) : scanner{scanner}
{
    // Set the chain
    componentHead = &alphaComp;
    componentHead->Chain(&numComp)->Chain(&strComp)->Chain(&miscComp);
}


Lexicons::Lexicon *Lexer::GetLexicon()
{
    if(!scanner->IsReady())
    {
        return nullptr;
    }

    return componentHead->GetLexicon(scanner);

}