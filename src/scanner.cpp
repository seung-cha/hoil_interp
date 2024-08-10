#include "scanner.h"
#include <iostream>
#include <exception>

Scanner::Scanner(std::string source) : stream{source}
{

}

Scanner::~Scanner()
{
    if(stream.is_open())
    {
        stream.close();
    }
}


char Scanner::ReadChar()
{
    if(stream.is_open())
    {
        return stream.get();
    }
    else
    {
        // TODO: Throw exception here
    }

}