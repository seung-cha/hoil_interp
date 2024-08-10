#ifndef SCANNER_H
#define SCANNER_H

#include <string>
#include <fstream>

#define BLANK_SPACE 4

class Scanner
{
    public:
    void ScanFile();
    Scanner(std::string source);
    ~Scanner();

    private:
    char currentChar = 0;
    int lineNo = 1, charNo = 0;

    /**
     * Get the next char that is not a whitespace.
     * Internally calls _readChar() and _trimBlanks().
     */
    bool Seek();
    void Match(char c);

    void _trimBlanks();
    char _peek();
    /**
     * Read a char and store it in currentChar.
     * Return False if EOF is read.
     */
    bool _readChar();
    std::ifstream stream;



};


#endif