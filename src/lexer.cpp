#include "lexer.h"
#include <cctype>
#include <sstream>

Lexicons::Lexicon *Lexer::GetLexicon()
{
    if(!scanner->IsReady())
    {
        return nullptr;
    }

    if(scanner->currentChar == '+')
    {
        int charNo = scanner->charNo;
        int lineNo = scanner->lineNo;
        scanner->Seek();
        return new Lexicons::Add(lineNo, charNo);
    }
    else if(scanner->currentChar == '-')
    {
        int charNo = scanner->charNo;
        int lineNo = scanner->lineNo;
        scanner->Seek();
        return new Lexicons::Sub(lineNo, charNo);
    }
    else if(scanner->currentChar == '*')
    {
        int charNo = scanner->charNo;
        int lineNo = scanner->lineNo;
        scanner->Seek();
        return new Lexicons::Mul(lineNo, charNo);
    }
    else if(scanner->currentChar == '/')
    {
        int charNo = scanner->charNo;
        int lineNo = scanner->lineNo;
        scanner->Seek();
        return new Lexicons::Div(lineNo, charNo);
    }
    else
    {
        std::ostringstream ss;
        int charNo;
        int lineNo;
        while(isdigit(scanner->currentChar))
        {
            ss << scanner->currentChar;
            lineNo = scanner->lineNo;
            charNo = scanner->charNo;
            scanner->Seek();
        }

        int32_t value = static_cast<int32_t>(std::stoi(ss.str()));
        return new Lexicons::Int(value, lineNo, charNo);

    }


}