#include "lexer.h"
#include <cctype>
#include <sstream>

Lexer::Lexer(Scanner *scanner) : scanner{scanner}
{
    // Set the chain
    componentHead = &opComp;
    componentHead->Chain(&numComp)->Chain(&alphaComp)->Chain(&strComp);
}


Lexicons::Lexicon *Lexer::GetLexicon()
{
    if(!scanner->IsReady())
    {
        return nullptr;
    }

    return componentHead->GetLexicon(scanner);

}