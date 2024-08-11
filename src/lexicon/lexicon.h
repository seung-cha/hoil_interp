#ifndef LEXICONE_H
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
        INT = 0,   REAL = 1,   BOOL = 2,  STRING = 3,
        TRUE = 50, FALSE = 51, IF = 52,   ELIF = 53,  ELSE = 54,
        FOR = 55,  WHILE = 56, DO = 57,   BREAK = 58, CONTINUE = 59,
        ADD = 100, SUB = 101,  MUL = 102, DIV = 103;


        public:
        LexiconId const Id;
        int const LineNo;
        int const CharNo;
        Lexicon(LexiconId t, int lineNo, int charNo) : Id{t}, LineNo{lineNo}, CharNo{charNo}
        {

        }
        virtual ~Lexicon()
        {
            
        }

        virtual std::string const ToString() const = 0;

        friend std::ostream& operator<<(std::ostream& os, Lexicon const& lex)
        {
            os << lex.ToString();
            return os;
        }

        std::string const Verbose() const
        {
            char str[2048];
            snprintf(str, 2048, "%s [%d, %d]", ToString().c_str(), LineNo, CharNo);
            return str;
        }

    };

}
#endif