#ifndef SCANNER_H
#define SCANNER_H

#include <string>
#include <fstream>

#define BLANK_SPACE 4

class Scanner
{
    public:
    char currentChar = 0;
    int lineNo = 1, charNo = 0;
    bool IsReady();
    /**
     * Get the next character, skipping all spaces inbetween.
     */
    char Seek();
    /**
     * Get the next character without skipping blanks.
     */
    char Next();
    /**
     * Trim all blanks untill a new char is found
     */
    void Trim();
    char Peek();
    void Match(char c);

    Scanner(std::string source);
    ~Scanner();
    private:
    void _trimBlanks();
    char _peek();
    /**
     * Read a char and store it in currentChar.
     */
    char _readChar();
    std::ifstream stream;



};


#endif