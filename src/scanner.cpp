#include "scanner.h"
#include <iostream>
#include <exception>
#include <cassert>

Scanner::Scanner(std::string source) : stream{source}
{
    if(IsReady())
    {
        _readChar();
        _trimBlanks();
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
    return stream.is_open();
}

char Scanner::Seek()
{
    // _trimBlanks() skips until currentChat is not a whitespace char.
    // If currentChar is non-whitespace, _trimBlank() does nothing. Next char could be a whitespace hence check the next char.
    // If currentChar is a whitespace, _trimBlank() will make sure currentChar is non-whitespace.
    if(!IsReady())
    {
        assert(false && "Attempt to call Seek() when stream is closed");
    }
    
    char const peek = _peek();
    if(currentChar == ' ' || currentChar == '\t' || currentChar == '#')
    {
        _trimBlanks();
        return currentChar;
    } 
    else if(peek == ' ' || peek == '\t' || peek == '#')
    {
        _readChar();
        _trimBlanks();
        return currentChar;
    }
    else
    {
        return _readChar();
    }
}

char Scanner::Next()
{
    return _readChar();
}

void Scanner::Trim()
{
    _trimBlanks();
}

char Scanner::Peek()
{
    return _peek();
}

char Scanner::_readChar()
{
    if(currentChar == EOF)
    {
        stream.close();
        return EOF;
    }

    charNo++;
    currentChar = stream.get();

    // TODO: better info on newline token
    if(currentChar == '\n')
    {
        charNo = 0;
        lineNo++;
    }


    return currentChar;
}

char Scanner::_peek()
{
    if(currentChar == EOF)
    {
        return EOF;
    }

    return stream.peek();
}

void Scanner::_trimBlanks()
{
    std::string temp;
    while(true)
    {
        switch(currentChar)
        {
            case ' ':
            break;
            case '\t':
            charNo += BLANK_SPACE - 1; // _readChar() increments it by 1
            break;
            // case '\n':
            // charNo = 0;    // _readChar() resets it to 0. 
            // lineNo++;
            // break;
            case '#':

            while(true)
            {
                //Skip the entire line
                getline(stream, temp);
                charNo = 0;
                lineNo++;

                if(_peek() == '#') _readChar();
                else break;
            }

            currentChar = '\n';
            return;
            break;
            default:
            return;
        }

        _readChar();
    }
}

