/**
 *  THIS LEXEME IS NOT USED
 */
#ifndef LEX_TRUE_H
#define LEX_TRUE_H

#include "../lexicon.h"
namespace Lexicons
{
    class True : public Lexicon
    {
        public:
        True(int lineNo, int charNo) : Lexicon{Lexicon::TRUE, "true", lineNo, charNo}
        {

        }

        std::string const ToString() const override
        {
            return "< TRUE, KWD >";
        }
    };

}

#endif