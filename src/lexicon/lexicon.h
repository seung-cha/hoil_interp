#ifndef LEXICON_H
#define LEXICONE_H

#include <iostream>
#include <string>
#include <cstdint>

namespace Lexicons
{
    using LexiconId = uint8_t;

    class Lexicon
    {
        public:
        LexiconId const static 
        INT = 0, REAL = 1, BOOL = 2, 
        ADD = 50, SUB = 51, MUL = 52, DIV = 53;


        public:
        LexiconId const Id;
        Lexicon(LexiconId t) : Id(t)
        {

        }

        virtual std::string const ToString() const = 0;

        friend std::ostream& operator<<(std::ostream& os, Lexicon const& lex)
        {
            os << lex.ToString();
            return os;
        }

    };

}
#endif