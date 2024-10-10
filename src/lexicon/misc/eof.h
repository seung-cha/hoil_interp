#ifndef LEX_EOF_H
#define LEX_EOF_H

#include "../lexicon.h"

namespace Lexicons
{
    class EndOfFile : public Lexicon
    {
        public:
        EndOfFile(int lineNo, int charNo) : Lexicon{Lexicon::END_OF_FILE, "$", lineNo, charNo}
        {

        }

        std::string const ToString() const override
        {
            return "< EOF, $ >";
        }
    };

}


#endif