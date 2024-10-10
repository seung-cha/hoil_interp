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
        INT             = 0,            REAL            = 1,            BOOL        = 2,            STRING      = 3,    // Types
        VOID            = 4,
        INTVAL          = 10,           REALVAL         = 11,           BOOLVAL     = 12,           STRINGVAL   = 13,

        TRUE            = 50,           FALSE           = 51,           IF          = 52,           ELIF        = 53,   // Keywords
        ELSE            = 54,           FOR             = 55,           WHILE       = 56,           DO          = 57,      
        BREAK           = 58,           CONTINUE        = 59,           LOOP        = 60,           RETURN      = 61,
        UNTIL           = 62,

        ADD             = 100,          SUB             = 101,          MUL         = 102,          DIV         = 103,  // Operators
        MOD             = 104,          ASSIGN          = 105,          ADD_ASSIGN  = 106,          SUB_ASSIGN  = 107,      
        MUL_ASSIGN      = 108,          DIV_ASSIGN      = 109,
        UNARY_ADD       = 110,          UNARY_SUB       = 111,                                                          // Unary Operations

        EQUAL           = 150,          NEQUAL          = 151,          NOT         = 152,                      // Boolean operators
        GREATER         = 153,          LESS            = 154,          GEQUAL      = 155,          LEQUAL      = 156,
        LOGICAL_OR      = 107,          LOGICAL_AND     = 108,
        // (                            // )                            // [                        // ]
        OPAREN          = 200,          CPAREN          = 201,          OSPAREN     = 202,          CSPAREN     = 203,  // Parenthesis
        // <                            // >
        OCURLY          = 204,          CCURLY          = 205,

        SEMICOLON       = 210,          COMMA           = 211,

        IDENTIFIER      = 250,          ERR             = 254,
        END_OF_FILE     = 255;


        public:
        LexiconId const Id;
        std::string const spelling;
        int const LineNo;
        int const CharNo;
        Lexicon(LexiconId t, std::string spelling, int lineNo, int charNo) : Id{t}, LineNo{lineNo}, CharNo{charNo}, spelling{spelling}
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