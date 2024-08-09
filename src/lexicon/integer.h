#include "lexicon.h"

namespace Lexicons
{
    class Integer : public Lexicon
    {
        public:
        int const value;

        Integer(int value) : Lexicon(Lexicon::INT), value(value)
        {

        }

        std::string const ToString() const override
        {
            char str[100];
            snprintf(str, 100, "< ADD, %d >", value);
            return str;
        }


    };


}