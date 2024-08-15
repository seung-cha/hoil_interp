#ifndef PARSER_H
#define PARSER_H
#include <vector>
#include <string>
#include "lexemes.h"

class Lexer;
namespace Lexicons
{
    class Lexicon;
}
class Parser
{
    public:
    Parser(Lexer *lexer);
    void Analyse();
    inline std::vector<std::string>& ErrorMsgs()
    {
        return errorMsgs;
    }

    private:
    void Next();
    /**
     * Match the current lexicon and get the next one.
     * Raise an error if Id doesn't match but don't terminate.
     */
    void Match(Lexicons::LexiconId id);
    Lexicons::Lexicon *currentLexicon;
    std::vector<std::string> errorMsgs;
    Lexer *lexer;




};

#endif