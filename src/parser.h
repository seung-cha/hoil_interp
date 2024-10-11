#ifndef PARSER_H
#define PARSER_H
#include <vector>
#include <string>
#include <memory>
#include "lexemes.h"
#include "AST.h"

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

    // Variable Decl
    void ParseVarDecl();
    void ParseVarDeclList();
    void ParseVarDeclExpr();

    // Func decl
    void ParseFuncDecl();

    // Param & Arg
    void ParseParamList();
    void ParseParam();

    std::unique_ptr<ASTs::List> ParseArgList();
    std::unique_ptr<ASTs::Arg> ParseArg();

    // Block
    void ParseItemList();
    void ParseItem();

    // Expr
    std::unique_ptr<ASTs::Expr> ParseExpr();
    std::unique_ptr<ASTs::Expr> ParseAssignmentExpr();
    std::unique_ptr<ASTs::Expr> ParseLogicalOrExpr();
    std::unique_ptr<ASTs::Expr> ParseLogicalAndExpr();
    std::unique_ptr<ASTs::Expr> ParseEqualityExpr();
    std::unique_ptr<ASTs::Expr> ParseRelationExpr();
    std::unique_ptr<ASTs::Expr> ParseAdditiveExpr();
    std::unique_ptr<ASTs::Expr> ParseMultiplicativeExpr();
    std::unique_ptr<ASTs::Expr> ParseUnaryExpr();
    std::unique_ptr<ASTs::Expr> ParsePrimaryExpr();


    // Stmt
    void ParseStmt();
    void ParseExprStmt();
    void ParseIfStmt();
    void ParseLoopStmt();
    void ParseJumpStmt();
    void ParseReturnStmt();
    void ParseCompoundStmt();
    
    std::unique_ptr<ASTs::Type> ParseType();
    std::unique_ptr<ASTs::Operator> ParseOperator();

    // Literals
    std::unique_ptr<ASTs::IntLiteral> ParseIntLiteral();
    std::unique_ptr<ASTs::RealLiteral> ParseRealLiteral();
    std::unique_ptr<ASTs::BoolLiteral> ParseBoolLiteral();
    std::unique_ptr<ASTs::StringLiteral> ParseStringLiteral();

    //Identifier
    std::unique_ptr<ASTs::Identifier> ParseIdentifier();
};

#endif