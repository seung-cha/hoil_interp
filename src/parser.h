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
    inline std::vector<std::string>& ErrorMsgs()
    {
        return errorMsgs;
    }

    private:
    /**
     * Return true if the current lexeme is of type Id.
     * Does not consume lexeme.
     */
    bool LexemeIs(Lexicons::LexiconId id); 
    /**
     * Get the next lexicon
     */
    void Next();
    /**
     * Match the current lexicon and get the next one.
     * Raise an error if Id doesn't match but don't terminate.
     */
    void Match(Lexicons::LexiconId id);
    /**
     * append a str to errorMsgs regarding current lexeme
     * and accept the next lexeme.
     */
    void ReportMismatch();

    Lexicons::Lexicon *currentLexicon;
    std::vector<std::string> errorMsgs;
    Lexer *lexer;

    // Parse functions
    // TODO: Build AST out of parse functions
    private:
    void ParseProgram();

    void ParseVarDecl();
    void ParseVarDeclList();
    void ParseVarDeclExpr();

    void ParseType();

    // Expr
    void ParseExpr();
    void ParseAssignmentExpr();
    void ParseLogicalOrExpr();
    void ParseLogicalAndExpr();
    void ParseEqualityExpr();
    void ParseAdditiveExpr();
    void ParseMultiplicativeExpr();
    void ParseUnaryExpr();
    void ParsePrimaryExpr();

    // Stmt
    void ParseStmt();
    void ParseExprStmt();
    void ParseIfStmt();
    void ParseLoopStmt();
    void ParseJumpStmt();
    void ParseReturnStmt();
};

#endif