#ifndef SCANNER_H
#define SCANNER_H

#include <string>
#include <fstream>

class Scanner
{
    public:
    Scanner(std::string source);
    ~Scanner();
    char ReadChar();

    private:
    std::ifstream stream;



};


#endif