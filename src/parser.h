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

    std::unique_ptr<ASTs::Program> program;

    private:
    int LineNo();
    int CharNo();
    std::string Spelling();
    /**
     * Return true if the current lexeme is of type Id.
     * Does not consume lexeme.
     */
    bool LexemeIs(Lexicons::LexiconId id); 

    /**
     * Return true if the current lexeme is instruct and the type is as specified.
     */
    bool InstructIs(InstructType type);

    /**
     * Return instruct lexeme; assuming it is one.
     */
    Lexicons::Instruct* GetInstruct();


    /**
     * Get the next lexicon
     */
    void Next();
    /**
     * Match the current lexicon and get the next one.
     * Raise an error if Id doesn't match but don't terminate.
     */
    bool Match(Lexicons::LexiconId id);
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
    std::unique_ptr<ASTs::Program> ParseProgram();

    // Variable Decl
    std::unique_ptr<ASTs::List> ParseLocalVarDeclList();    // ATM this is just a wrapper to VarDeclList

    std::unique_ptr<ASTs::Decl> ParseVarDecl();
    std::unique_ptr<ASTs::List> ParseVarDeclList();
    std::unique_ptr<ASTs::Expr>  ParseVarDeclExpr();

    // Func decl
    std::unique_ptr<ASTs::List> ParseFuncDeclList();
    std::unique_ptr<ASTs::Decl> ParseFuncDecl();

    // Param & Arg
    std::unique_ptr<ASTs::List> ParseParamList();
    std::unique_ptr<ASTs::Param> ParseParam();

    std::unique_ptr<ASTs::List> ParseArgList();
    std::unique_ptr<ASTs::Arg> ParseArg();

    // Block
    std::unique_ptr<ASTs::List> ParseItemList();
    std::unique_ptr<ASTs::Block> ParseItem();

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
    std::unique_ptr<ASTs::Stmt> ParseStmt();
    std::unique_ptr<ASTs::Stmt> ParseExprStmt();
    std::unique_ptr<ASTs::Stmt> ParseIfStmt();
    std::unique_ptr<ASTs::List> ParseElifList();
    std::unique_ptr<ASTs::Stmt> ParseLoopStmt();
    std::unique_ptr<ASTs::Stmt> ParseJumpStmt();
    std::unique_ptr<ASTs::Stmt> ParseReturnStmt();
    std::unique_ptr<ASTs::Stmt> ParseCompoundStmt();
    std::unique_ptr<ASTs::Stmt> ParseInstructStmt();
    std::unique_ptr<ASTs::Stmt> ParseCallStmt();
    
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