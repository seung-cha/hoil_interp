#include "scanner.h"
#include <iostream>
#include <exception>
#include <cassert>

Scanner::Scanner(std::string source) : stream{source}
{
    if(IsReady())
    {
        Seek();
    }
}

Scanner::~Scanner()
{
    if(stream.is_open())
    {
        stream.close();
    }
}

bool Scanner::IsReady()
{
    return stream.is_open() && currentChar != EOF;
}

char Scanner::Seek()
{
    _trimBlanks();
    return _readChar();
}

void Scanner::Match(char c)
{
    if(currentChar == c)
    {
        Seek();
    }
    else
    {
        // TODO:: Throw an exception here
    }
}


char Scanner::_readChar()
{
    if(IsReady())
    {
        charNo++;
        currentChar = stream.get();
        return currentChar;
    }
    else
    {
        // TODO: Throw exception here
    }

    return currentChar;
}

char Scanner::_peek()
{
    return stream.peek();
}

void Scanner::_trimBlanks()
{
    while(true)
    {
        switch(_peek())
        {
            case ' ':
            break;
            case '\t':
            charNo += BLANK_SPACE - 1; // _readChar() increments it by 1
            break;
            case '\n':
            charNo = -1;    // _readChar() resets it to 0. 
            lineNo++;
            break;

            default:
            return;
        }

        _readChar();
    }
}

