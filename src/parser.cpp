#include <sstream>
#include "lexer.h"
#include "parser.h"

using namespace Lexicons;

Parser::Parser(Lexer *lexer) : lexer{lexer}
{
    Next(); // Grab the first token
    program = ParseProgram();
}

void Parser::Next()
{
    currentLexicon = lexer->GetLexicon();
}

int Parser::LineNo()
{
    if(!currentLexicon)
        return 0;

    return currentLexicon->LineNo;
}

int Parser::CharNo()
{
    if(!currentLexicon)
        return 0;
    
    return currentLexicon->CharNo;
}

std::string Parser::Spelling()
{
    if(!currentLexicon)
        return "";
        
    return currentLexicon->spelling;
}

bool Parser::LexemeIs(Lexicons::LexiconId id)
{
    if(!currentLexicon)
        return false;
    

    return currentLexicon->Id == id;
}

bool Parser::Match(Lexicons::LexiconId id)
{
    bool matched = true;
    if(!currentLexicon || currentLexicon->Id != id)
    {
        ReportMismatch();
        matched = false;
    }
    
    if(currentLexicon)
    {
        Next();
    }

    return matched;
}

void Parser::ReportMismatch()
{
    if(!currentLexicon)
    {
        errorMsgs.push_back("Found No more tokens while processing");
    }
    else
    {
        std::ostringstream ss;
        ss << "Unexpected Token: " << currentLexicon->Verbose() << " (" << LineNo() << ", " << CharNo() << ")";
        errorMsgs.push_back(ss.str());
        //Next();
    }
}


std::unique_ptr<ASTs::Program> Parser::ParseProgram()
{
    std::unique_ptr<ASTs::List> list = std::make_unique<ASTs::EmptyBlockList>();
    
    // Trip the new lines first
    while(LexemeIs(Lexicon::NEWLINE))
    {
        Next();
    }

    if(!LexemeIs(Lexicon::END_OF_FILE))
    {
        list = ParseItemList();
    }


    Match(Lexicon::END_OF_FILE);

    return std::make_unique<ASTs::Program>(list.release(), LineNo(), CharNo());
}

std::unique_ptr<ASTs::List> Parser::ParseLocalVarDeclList()
{
    auto type = ParseType();
    auto list = ParseVarDeclList();
    Match(Lexicon::SEMICOLON);

    // Assign type to each decl
    for(ASTs::VarDeclList *declList = dynamic_cast<ASTs::VarDeclList*>(list.get()); declList; declList = dynamic_cast<ASTs::VarDeclList*>(declList->next.get()))
    {
        declList->decl->type = std::move(type->DeepCopy());
    }

    return list;
}

std::unique_ptr<ASTs::List> Parser::ParseVarDeclList()
{
    auto expr = ParseVarDecl();

    std::unique_ptr<ASTs::List> next = std::make_unique<ASTs::EmptyVarDeclList>();
    if(currentLexicon->Id == Lexicon::COMMA)
    {
        Next();
        next = ParseVarDeclList();
    }

    return std::make_unique<ASTs::VarDeclList>(expr.release(), next.release());
}

std::unique_ptr<ASTs::Decl> Parser::ParseVarDecl()
{
    auto ident = ParseIdentifier();
    std::unique_ptr<ASTs::Type> type{};
    std::unique_ptr<ASTs::Expr> expr{};

    if(LexemeIs(Lexicon::IS))
    {
        Next();

        if(LexemeIs(Lexicon::REAL) || LexemeIs(Lexicon::BOOL) || 
        LexemeIs(Lexicon::STRING) || LexemeIs(Lexicon::OBJECT))
        {
            type = std::move(ParseType());
        }
        else
        {
            expr = std::move(ParseExpr());
        }
    }

    // Fill Type later
    return std::make_unique<ASTs::VarDecl>(type.release(), ident.release(), expr.release(), LineNo(), CharNo());
}


std::unique_ptr<ASTs::Expr> Parser::ParseVarDeclExpr()
{
    std::unique_ptr<ASTs::Expr> expr{};
    if(LexemeIs(Lexicon::ASSIGN))
    {
        Next();
        expr = ParseExpr();
    }
    else
    {
        expr = std::make_unique<ASTs::EmptyExpr>(LineNo(), CharNo());
    }

    return std::make_unique<ASTs::VarDeclExpr>(expr.release(), LineNo(), CharNo());
}

std::unique_ptr<ASTs::List> Parser::ParseFuncDeclList()
{
    auto decl = ParseFuncDecl();
    std::unique_ptr<ASTs::List> list = std::make_unique<ASTs::EmptyFuncDeclList>();

    if( LexemeIs(Lexicon::INT)  ||
        LexemeIs(Lexicon::REAL) ||
        LexemeIs(Lexicon::BOOL) ||
        LexemeIs(Lexicon::STRING) ||
        LexemeIs(Lexicon::VOID))
    {
        list = ParseFuncDeclList();
    }

    return std::make_unique<ASTs::FuncDeclList>(decl.release(), list.release());
}

std::unique_ptr<ASTs::Decl> Parser::ParseFuncDecl()
{
    auto type = ParseType();
    auto ident = ParseIdentifier();

    Match(Lexicon::OPAREN);

    std::unique_ptr<ASTs::List> params = std::make_unique<ASTs::EmptyParamList>();
    if(!LexemeIs(Lexicon::CPAREN))
    {
        params = ParseParamList();
    }

    Match(Lexicon::CPAREN);

    auto stmt = ParseCompoundStmt();

    return std::make_unique<ASTs::FuncDecl>(type.release(), ident.release(), params.release(), stmt.release(), LineNo(), CharNo());
}

std::unique_ptr<ASTs::List> Parser::ParseParamList()
{
    auto param = ParseParam();
    std::unique_ptr<ASTs::List> paramList{};
    if(LexemeIs(Lexicon::COMMA))
    {
        Next();
        paramList = ParseParamList();
    }
    else
    {
        paramList = std::make_unique<ASTs::EmptyParamList>();
    }

    return std::make_unique<ASTs::ParamList>(param.release(), paramList.release());
}

std::unique_ptr<ASTs::Param> Parser::ParseParam()
{
    auto type = ParseType();
    auto iden = ParseIdentifier();

    return std::make_unique<ASTs::Param>(type.release(), iden.release(), LineNo(), CharNo());
}

std::unique_ptr<ASTs::List> Parser::ParseArgList()
{
    std::unique_ptr<ASTs::ArgList> list{};
    auto arg = ParseArg();
    if(LexemeIs(Lexicon::COMMA))
    {
        Next();
        auto list2 = ParseArgList();

        list = std::make_unique<ASTs::ArgList>(arg.release(), list2.release());
    }
    else
    {
        list = std::make_unique<ASTs::ArgList>(arg.release(), new ASTs::EmptyArgList());
    }

    return list;
}

std::unique_ptr<ASTs::Arg> Parser::ParseArg()
{
    return std::make_unique<ASTs::Arg>(ParseExpr().release(), LineNo(), CharNo());
}

std::unique_ptr<ASTs::Type> Parser::ParseType()
{
    std::unique_ptr<ASTs::Type> ptr{};
    switch(currentLexicon->Id)
    {
        case Lexicon::INT:
        Next();
        ptr = std::make_unique<ASTs::IntType>(LineNo(), CharNo());
        break;
        case Lexicon::REAL:
        Next();
        ptr = std::make_unique<ASTs::RealType>(LineNo(), CharNo());
        break;
        case Lexicon::BOOL:
        Next();
        ptr = std::make_unique<ASTs::BoolType>(LineNo(), CharNo());
        break;
        case Lexicon::VOID:
        Next();
        ptr = std::make_unique<ASTs::VoidType>(LineNo(), CharNo());
        break;
        case Lexicon::STRING:
        Next();
        ptr = std::make_unique<ASTs::StringType>(LineNo(), CharNo());
        break;
        default:
        ptr = std::make_unique<ASTs::ErrorType>(LineNo(), CharNo());
        ReportMismatch();
    }
    return ptr;
}

std::unique_ptr<ASTs::Expr> Parser::ParseExpr()
{
    return ParseLogicalOrExpr();
}

std::unique_ptr<ASTs::Expr> Parser::ParseAssignmentExpr()
{
    std::unique_ptr<ASTs::Expr> expr1 = ParseLogicalOrExpr();

    if(LexemeIs(Lexicon::ASSIGN) ||
        LexemeIs(Lexicon::ADD_ASSIGN)||
        LexemeIs(Lexicon::SUB_ASSIGN)||
        LexemeIs(Lexicon::MUL_ASSIGN)||
        LexemeIs(Lexicon::DIV_ASSIGN))
        {
            auto op = ParseOperator();
            auto expr2 = ParseAssignmentExpr();

            expr1 = std::make_unique<ASTs::AssignExpr>(expr1.release(), expr2.release(), op.release(), LineNo(), CharNo());
        }

    return expr1;
}

std::unique_ptr<ASTs::Expr> Parser::ParseLogicalOrExpr()
{
    std::unique_ptr<ASTs::Expr> expr1 = ParseLogicalAndExpr();
    if(LexemeIs(Lexicon::LOGICAL_OR))
    {
        auto op = ParseOperator();
        auto expr2 = ParseLogicalOrExpr();
        expr1 = std::make_unique<ASTs::BinaryExpr>(expr1.release(), expr2.release(), op.release(), LineNo(), CharNo());
    }

    return expr1;
}

std::unique_ptr<ASTs::Expr> Parser::ParseLogicalAndExpr()
{
    std::unique_ptr<ASTs::Expr> expr1 = ParseEqualityExpr();
    if(LexemeIs(Lexicon::LOGICAL_AND))
    {
        auto op = ParseOperator();
        auto expr2 = ParseLogicalAndExpr();
        expr1 = std::make_unique<ASTs::BinaryExpr>(expr1.release(), expr2.release(), op.release(), LineNo(), CharNo());
    }

    return expr1;
}

std::unique_ptr<ASTs::Expr> Parser::ParseEqualityExpr()
{
    std::unique_ptr<ASTs::Expr> expr1 = ParseRelationExpr();

    if(LexemeIs(Lexicon::EQUAL) || LexemeIs(Lexicon::NEQUAL))
    {
        auto op = ParseOperator();
        auto expr2 = ParseEqualityExpr();
        expr1 = std::make_unique<ASTs::BinaryExpr>(expr1.release(), expr2.release(), op.release(), LineNo(), CharNo());
    }

    return expr1;
}

std::unique_ptr<ASTs::Expr> Parser::ParseRelationExpr()
{
    std::unique_ptr<ASTs::Expr> expr1 = ParseAdditiveExpr();

    if(
        LexemeIs(Lexicon::LESS) || LexemeIs(Lexicon::LEQUAL) ||
        LexemeIs(Lexicon::GREATER) || LexemeIs(Lexicon::GEQUAL))
    {
        auto op = ParseOperator();
        auto expr2 = ParseRelationExpr();
        expr1 = std::make_unique<ASTs::BinaryExpr>(expr1.release(), expr2.release(), op.release(), LineNo(), CharNo());
    }

    return expr1;
}

std::unique_ptr<ASTs::Expr> Parser::ParseAdditiveExpr()
{
    std::unique_ptr<ASTs::Expr> expr1 = ParseMultiplicativeExpr();

    if(LexemeIs(Lexicon::ADD) || LexemeIs(Lexicon::SUB))
    {
        auto op = ParseOperator();
        auto expr2 = ParseAdditiveExpr();

        expr1 = std::make_unique<ASTs::BinaryExpr>(expr1.release(), expr2.release(), op.release(), LineNo(), CharNo());
    }

    return expr1;
}

std::unique_ptr<ASTs::Expr> Parser::ParseMultiplicativeExpr()
{
    std::unique_ptr<ASTs::Expr> expr1 = ParseUnaryExpr();

    if(LexemeIs(Lexicon::MUL) || 
          LexemeIs(Lexicon::DIV) || 
          LexemeIs(Lexicon::MOD))
    {
        auto op = ParseOperator();
        auto expr2 = ParseMultiplicativeExpr();
        expr1 = std::make_unique<ASTs::BinaryExpr>(expr1.release(), expr2.release(), op.release(), LineNo(), CharNo());
    }
    return expr1;
}

std::unique_ptr<ASTs::Expr> Parser::ParseUnaryExpr()
{  
    if( LexemeIs(Lexicon::UNARY_ADD) || LexemeIs(Lexicon::ADD) || LexemeIs(Lexicon::UNARY_SUB) 
     || LexemeIs(Lexicon::SUB)       || LexemeIs(Lexicon::NOT))
    {
        auto op = ParseOperator();
        auto expr2 = ParseUnaryExpr();

        return std::make_unique<ASTs::PreUnaryExpr>(expr2.release(), op.release(), LineNo(), CharNo());
    }
    else
    {
        return ParsePrimaryExpr();
    }
}

std::unique_ptr<ASTs::Expr> Parser::ParsePrimaryExpr()
{
    std::unique_ptr<ASTs::Expr> expr{};

    if(LexemeIs(Lexicon::IDENTIFIER))
    {
        auto identifier = ParseIdentifier();

        // Check function call, post ++ or --
        if(LexemeIs(Lexicon::OPAREN))
        {
            Next();
            ASTs::List *argList = nullptr;
            if(!LexemeIs(Lexicon::CPAREN))
            {
                argList = ParseArgList().release();
            }
            else
            {
                argList = new ASTs::EmptyArgList();
            }
            Match(Lexicon::CPAREN);

            expr = std::make_unique<ASTs::FunctionCallExpr>(identifier.release(), argList, LineNo(), CharNo());
        }
        else if(LexemeIs(Lexicon::UNARY_ADD) || LexemeIs(Lexicon::UNARY_SUB))
        {
            auto op = ParseOperator();
            auto var = new ASTs::VariableExpr(new ASTs::Variable(identifier.release(), LineNo(), CharNo()));

            expr = std::make_unique<ASTs::PostUnaryExpr>(var, op.release(), LineNo(), CharNo());
        }
        else
        {
            expr = std::make_unique<ASTs::VariableExpr>(new ASTs::Variable(identifier.release(), LineNo(), CharNo()));
        }
    }
    else if(LexemeIs(Lexicon::INTVAL))
    {
        auto intLiteral = ParseIntLiteral();
        expr = std::make_unique<ASTs::IntExpr>(intLiteral.release());
    }
    else if(LexemeIs(Lexicon::REALVAL))
    {
        auto realLiteral = ParseRealLiteral();
        expr = std::make_unique<ASTs::RealExpr>(realLiteral.release());
    }
    else if(LexemeIs(Lexicon::BOOLVAL))
    {
        auto boolLiteral = ParseBoolLiteral();
        expr = std::make_unique<ASTs::BoolExpr>(boolLiteral.release());
    }
    else if(LexemeIs(Lexicon::STRINGVAL))
    {
        auto stringLiteral = ParseStringLiteral();
        expr = std::make_unique<ASTs::StringExpr>(stringLiteral.release());
    }
    else if(LexemeIs(Lexicon::OPAREN))
    {
        Next();
        expr = ParseExpr();
        Match(Lexicon::CPAREN);
    }
    else
    {
        ReportMismatch();
        expr = std::make_unique<ASTs::ErrorExpr>(LineNo(), CharNo());
    }

    return expr;
}

std::unique_ptr<ASTs::Stmt> Parser::ParseStmt()
{
    // Assume new lines are trimmed
    if(LexemeIs(Lexicon::GREATER))
    {
        return ParseInstructStmt();
    }
    else if(LexemeIs(Lexicon::IDENTIFIER))
    {
        // This is really just a decl stmt
        return ParseExprStmt();
    }
    else
    {
        ReportMismatch();
        return std::make_unique<ASTs::ErrorStmt>(LineNo(), CharNo());
    }

    // if(LexemeIs(Lexicon::IF))
    // {
    //     return ParseIfStmt();
    // }
    // else if(LexemeIs(Lexicon::LOOP))
    // {
    //     return ParseLoopStmt();
    // }
    // else if(LexemeIs(Lexicon::CONTINUE) || LexemeIs(Lexicon::BREAK))
    // {
    //     return ParseJumpStmt();
    // }
    // else if(LexemeIs(Lexicon::RETURN))
    // {
    //     return ParseReturnStmt();
    // }
    // else if(LexemeIs(Lexicon::OCURLY))
    // {
    //     return ParseCompoundStmt();
    // }
    // else
    // {
    //     return ParseExprStmt();
    // }
}

std::unique_ptr<ASTs::Stmt> Parser::ParseInstructStmt()
{
    Match(Lexicon::GREATER);
    auto str = ParseStringLiteral();
    Match(Lexicon::NEWLINE);

    return std::make_unique<ASTs::InstructStmt>(str.release(), LineNo(), CharNo());


}

std::unique_ptr<ASTs::Stmt> Parser::ParseExprStmt()
{
    
    auto decl = ParseVarDecl();
    Match(Lexicon::NEWLINE);

    return std::make_unique<ASTs::DeclStmt>(decl.release(), LineNo(), CharNo());

}

std::unique_ptr<ASTs::Stmt> Parser::ParseIfStmt()
{
    Match(Lexicon::IF);

    Match(Lexicon::OPAREN);
    auto ifCond = ParseExpr();
    Match(Lexicon::CPAREN);
    Match(Lexicon::NEWLINE);

    auto ifBody = ParseStmt();

    std::unique_ptr<ASTs::List> elifList{};
    if(LexemeIs(Lexicon::ELIF))
    {
        elifList = ParseElifList();
    }
    else
    {
        elifList = std::make_unique<ASTs::EmptyElifList>();
    }


    std::unique_ptr<ASTs::Stmt> elseStmt{};
    if(LexemeIs(Lexicon::ELSE))
    {
        Next();
        Match(Lexicon::NEWLINE);
        elseStmt = ParseStmt();
    }
    else
    {
        elseStmt = std::make_unique<ASTs::EmptyStmt>(LineNo(), CharNo());
    }

    return std::make_unique<ASTs::IfStmt>(ifCond.release(), ifBody.release(), elifList.release(), elseStmt.release(), LineNo(), CharNo());
}

std::unique_ptr<ASTs::List> Parser::ParseElifList()
{
    Match(Lexicon::ELIF);
    Match(Lexicon::OPAREN);

    auto cond = ParseExpr();
    Match(Lexicon::CPAREN);
    Match(Lexicon::NEWLINE);

    auto stmt = ParseStmt();

    std::unique_ptr<ASTs::ElifStmt> elif = std::make_unique<ASTs::ElifStmt>(cond.release(), stmt.release(), LineNo(), CharNo());

    if(LexemeIs(Lexicon::ELIF))
    {
        auto list = ParseElifList();
        return std::make_unique<ASTs::ElifList>(elif.release(), list.release());
    }
    else
    {
        return std::make_unique<ASTs::ElifList>(elif.release(), new ASTs::EmptyElifList());
    }


}

std::unique_ptr<ASTs::Stmt> Parser::ParseLoopStmt()
{
    std::unique_ptr<ASTs::Stmt> stmt{};

    Match(Lexicon::LOOP);
    if(!LexemeIs(Lexicon::OPAREN))
    {
        // Handle LOOP UNTIL
        auto body = ParseStmt();
        Match(Lexicon::UNTIL);
        Match(Lexicon::OPAREN);
        auto cond = ParseExpr();
        Match(Lexicon::CPAREN);
        Match(Lexicon::SEMICOLON);

        stmt = std::make_unique<ASTs::DoWhileStmt>(cond.release(), body.release(), LineNo(), CharNo());
    }
    else
    {
        Match(Lexicon::OPAREN);

        if(LexemeIs(Lexicon::INT) || LexemeIs(Lexicon::REAL) || 
        LexemeIs(Lexicon::STRING) || LexemeIs(Lexicon:: VOID))
        {
            // For-loop like form
            auto list = ParseLocalVarDeclList();
            auto cond = ParseExprStmt();
            auto postOp = ParseExpr();
            Match(Lexicon::CPAREN);

            auto body = ParseStmt();

            stmt = std::make_unique<ASTs::ForStmt>(list.release(), cond.release(), postOp.release(), body.release(), LineNo(), CharNo());

        }
        else
        {
            // While-loop like form
            auto cond = ParseExpr();
            Match(Lexicon::CPAREN);
            auto body = ParseStmt();

            stmt = std::make_unique<ASTs::WhileStmt>(cond.release(), body.release(), LineNo(), CharNo());
        }

    }

    return stmt;
}

std::unique_ptr<ASTs::Stmt> Parser::ParseJumpStmt()
{
    std::unique_ptr<ASTs::Stmt> stmt{};
    if(LexemeIs(Lexicon::CONTINUE))
    {
        Next();
        stmt = std::make_unique<ASTs::ContinueStmt>(LineNo(), CharNo());
    }
    else
    {
        Match(Lexicon::BREAK);
        stmt = std::make_unique<ASTs::BreakStmt>(LineNo(), CharNo());

    }

    Match(Lexicon::SEMICOLON);
    return stmt;
}

std::unique_ptr<ASTs::Stmt> Parser::ParseReturnStmt()
{
    Match(Lexicon::RETURN);
    return std::make_unique<ASTs::ReturnStmt>(ParseExprStmt().release(), LineNo(), CharNo());
}

std::unique_ptr<ASTs::Stmt> Parser::ParseCompoundStmt()
{
    if(!Match(Lexicon::OCURLY))
    {
        return std::make_unique<ASTs::ErrorStmt>(LineNo(), CharNo());
    }

    std::unique_ptr<ASTs::List> list = std::make_unique<ASTs::EmptyBlockList>();
    if(!LexemeIs(Lexicon::CCURLY))
    {
        list = ParseItemList();
    }

    Match(Lexicon::CCURLY);
    return std::make_unique<ASTs::CompoundStmt>(list.release(), LineNo(), CharNo());
}


std::unique_ptr<ASTs::List> Parser::ParseItemList()
{
    auto item = ParseItem();

    while(LexemeIs(Lexicon::NEWLINE))
    {
        Next();
    }

    std::unique_ptr<ASTs::List> blockList = std::make_unique<ASTs::EmptyBlockList>();

    if(!LexemeIs(Lexicon::END_OF_FILE))
    {
        blockList = ParseItemList();
    }

    return std::make_unique<ASTs::BlockItemList>(item.release(), blockList.release());
}

std::unique_ptr<ASTs::Block> Parser::ParseItem()
{
    std::unique_ptr<ASTs::Block> block{};
    
    auto stmt = ParseStmt();
    block = std::make_unique<ASTs::StmtBlock>(stmt.release(), LineNo(), CharNo());
    

    return block;
}

std::unique_ptr<ASTs::Operator> Parser::ParseOperator()
{
    // TODO: Handle
    auto op = std::make_unique<ASTs::Operator>(currentLexicon->spelling, LineNo(), CharNo());

    Next();
    return op;
}

std::unique_ptr<ASTs::IntLiteral> Parser::ParseIntLiteral()
{
    auto literal = std::make_unique<ASTs::IntLiteral>(currentLexicon->spelling, LineNo(), CharNo());
    Next();

    return literal;
}

std::unique_ptr<ASTs::RealLiteral> Parser::ParseRealLiteral()
{
    auto literal = std::make_unique<ASTs::RealLiteral>(currentLexicon->spelling, LineNo(), CharNo());
    Next();

    return literal;
}

std::unique_ptr<ASTs::BoolLiteral> Parser::ParseBoolLiteral()
{
    auto literal = std::make_unique<ASTs::BoolLiteral>(currentLexicon->spelling, LineNo(), CharNo());
    Next();

    return literal;
}

std::unique_ptr<ASTs::StringLiteral> Parser::ParseStringLiteral()
{
    auto literal = std::make_unique<ASTs::StringLiteral>(currentLexicon->spelling, LineNo(), CharNo());
    Next();

    return literal;
}

std::unique_ptr<ASTs::Identifier> Parser::ParseIdentifier()
{
    auto ident = std::make_unique<ASTs::Identifier>(currentLexicon->spelling, LineNo(), CharNo());
    Next();

    return ident;
}
