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

bool Parser::InstructIs(InstructType type)
{
    Lexicons::Instruct *instruct = dynamic_cast<Lexicons::Instruct*>(currentLexicon);
    
    if(!instruct)
    {
        return false;
    }

    return instruct->type == type;
}

Lexicons::Instruct* Parser::GetInstruct()
{
    return static_cast<Lexicons::Instruct*>(currentLexicon);
}

bool Parser::Match(Lexicons::LexiconId id)
{
    bool matched = true;
    if(!currentLexicon || currentLexicon->Id != id)
    {
        ReportMismatch();
        matched = false;
    }
    else if(!LexemeIs(Lexicon::END_OF_FILE))
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

        // TODO: Hot fix
        if(!LexemeIs(Lexicon::END_OF_FILE))
        {
            Next();
        }
    }
}


std::unique_ptr<ASTs::Program> Parser::ParseProgram()
{
    std::unique_ptr<ASTs::List> list = std::make_unique<ASTs::EmptyBlockList>();
    
    // Trim the new lines first
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
    std::unique_ptr<ASTs::Type> type = std::make_unique<ASTs::VoidType>(0, 0);  // Denotes none type
    std::unique_ptr<ASTs::Expr> expr = std::make_unique<ASTs::EmptyExpr>(0, 0);


    // Check if it's array assignment
    if(LexemeIs(Lexicon::OSPAREN))
    {
        Next();
        ASTs::Expr *index = ParseExpr().release();
        Match(Lexicon::CSPAREN);

        Match(Lexicon::IS);
        expr = std::move(ParseExpr());
        return std::make_unique<ASTs::ArrDecl>(ident.release(), index, expr.release(), LineNo(), CharNo());
    }

    Match(Lexicon::IS);

    if(LexemeIs(Lexicon::REAL) || LexemeIs(Lexicon::BOOL) || LexemeIs(Lexicon::STRING)
    || LexemeIs(Lexicon::OBJECT) || LexemeIs(Lexicon::ATTRIBUTE) || LexemeIs(Lexicon::ARRAY))
    {
        type = std::move(ParseType());

        if(LexemeIs(Lexicon::COLON))
        {
            Next();
            expr = std::move(ParseExpr());
        }
    }
    else
    {
        expr = std::move(ParseExpr());
    }

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
    Match(Lexicon::DEFINE);

    auto ident = ParseIdentifier();

    std::unique_ptr<ASTs::List> paramList = std::make_unique<ASTs::EmptyParamList>();
    if(LexemeIs(Lexicon::OPAREN))
    {
        Next();
        if(!LexemeIs(Lexicon::CPAREN))
        {
            paramList = ParseParamList();
        }
        
        Match(Lexicon::CPAREN);
    }

    std::unique_ptr<ASTs::Type> retType = std::make_unique<ASTs::VoidType>(0, 0);
    
    if(LexemeIs(Lexicon::RIGHT_ARR))
    {
        Next();
        retType = ParseType();
    }

    Match(Lexicon::NEWLINE);
    auto stmt = ParseCompoundStmt();

    return std::make_unique<ASTs::FuncDecl>(retType.release(), ident.release(), paramList.release(), stmt.release(), LineNo(), CharNo());
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
    auto iden = ParseIdentifier();
    std::unique_ptr<ASTs::Type> type = std::make_unique<ASTs::VoidType>(0, 0);

    if(LexemeIs(Lexicon::COLON))
    {
        Next();
        type = ParseType();
    }

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
        case Lexicon::OBJECT:
        Next();
        ptr = std::make_unique<ASTs::ObjectType>(LineNo(), CharNo());
        break;
        case Lexicon::ATTRIBUTE:
        Next();
        ptr = std::make_unique<ASTs::AttributeType>(LineNo(), CharNo());
        break;
        case Lexicon::ARRAY:
        Next();
        ptr = std::make_unique<ASTs::ArrayType>(LineNo(), CharNo());
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

    if(LexemeIs(Lexicon::EQUAL) || LexemeIs(Lexicon::NEQUAL) || LexemeIs(Lexicon::IS) || LexemeIs(Lexicon::NOT_KWD) || LexemeIs(Lexicon::EQUAL_KWD))
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
     || LexemeIs(Lexicon::SUB)       || LexemeIs(Lexicon::NOT) || LexemeIs(Lexicon::NOT_KWD))
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

        // Check function call, post ++ or --, or arrayExpr
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
        else if(LexemeIs(Lexicon::OSPAREN))
        {
            Next();
            ASTs::Expr *index = ParseExpr().release(); // Index
            Match(Lexicon::CSPAREN);  
            
            expr = std::make_unique<ASTs::ArrayExpr>(identifier.release(), index, LineNo(), CharNo());
        }
        else
        {
            expr = std::make_unique<ASTs::VariableExpr>(new ASTs::Variable(identifier.release(), LineNo(), CharNo()));
        }
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
    //Assume new lines are trimmed
    if(InstructIs(Instruct::Type_Expr))
    {
        return ParseInstructStmt();
    } 
    else if(LexemeIs(Lexicon::IF) || InstructIs(Instruct::Type_Conditional))
    {
        return ParseIfStmt();
    }
    else if(LexemeIs(Lexicon::LOOP) || InstructIs(Instruct::Type_Loop))
    {
        return ParseLoopStmt();
    }
    else if(LexemeIs(Lexicon::BREAK) || LexemeIs(Lexicon::CONTINUE))
    {
        return ParseJumpStmt();
    }
    else if(LexemeIs(Lexicon::OCURLY))
    {
        return ParseCompoundStmt();
    }
    else if(LexemeIs(Lexicon::IDENTIFIER) || LexemeIs(Lexicon::DEFINE))
    {
        // This is really just a decl stmt
        return ParseExprStmt();
    }
    else if(LexemeIs(Lexicon::CALL))
    {
        return ParseCallStmt();
    }
    else if(LexemeIs(Lexicon::RETURN))
    {
        return ParseReturnStmt();
    }
    else
    {
        ReportMismatch();
        return std::make_unique<ASTs::ErrorStmt>(LineNo(), CharNo());
    }

}

std::unique_ptr<ASTs::Stmt> Parser::ParseCallStmt()
{
    Match(Lexicon::CALL);
    auto ident = ParseIdentifier();
    std::unique_ptr<ASTs::List> argList = std::make_unique<ASTs::EmptyArgList>();

    if(LexemeIs(Lexicon::OPAREN))
    {
        Next();

        if(!LexemeIs(Lexicon::CPAREN))
        {
            argList = ParseArgList();
        }
        Match(Lexicon::CPAREN);
    }

    Match(Lexicon::NEWLINE);
    return std::make_unique<ASTs::CallStmt>(ident.release(), argList.release(), LineNo(), CharNo());
}

std::unique_ptr<ASTs::Stmt> Parser::ParseInstructStmt()
{
    auto instruct = GetInstruct();
    Next();

    return std::make_unique<ASTs::InstructStmt>(instruct->value, LineNo(), CharNo());


}

std::unique_ptr<ASTs::Stmt> Parser::ParseExprStmt()
{
    std::unique_ptr<ASTs::Decl> decl{nullptr};
    if(LexemeIs(Lexicon::DEFINE))
    {
        decl = ParseFuncDecl();
    }
    else
    {
        decl = ParseVarDecl();
    }

    Match(Lexicon::NEWLINE);

    return std::make_unique<ASTs::DeclStmt>(decl.release(), LineNo(), CharNo());

}

std::unique_ptr<ASTs::Stmt> Parser::ParseIfStmt()
{
    std::unique_ptr<ASTs::Expr> ifCond;
    if(InstructIs(Instruct::Type_Conditional))
    {
        auto instruct = GetInstruct();
        ifCond = std::make_unique<ASTs::InstructExpr>(instruct->type, instruct->value);
        Next();
    }
    else
    {
        Match(Lexicon::IF);
        ifCond = std::move(ParseExpr());
        Match(Lexicon::NEWLINE);
    }


    auto ifBody = ParseStmt();

    std::unique_ptr<ASTs::List> elifList = std::make_unique<ASTs::EmptyElifList>();
    if(LexemeIs(Lexicon::ELIF))
    {
        elifList = std::move(ParseElifList());
    }


    std::unique_ptr<ASTs::Stmt> elseStmt = std::make_unique<ASTs::EmptyStmt>(LineNo(), CharNo());
    if(LexemeIs(Lexicon::ELSE))
    {
        Next();
        Match(Lexicon::NEWLINE);
        elseStmt = std::move(ParseStmt());
    }

    return std::make_unique<ASTs::IfStmt>(ifCond.release(), ifBody.release(), elifList.release(), elseStmt.release(), LineNo(), CharNo());
}

std::unique_ptr<ASTs::List> Parser::ParseElifList()
{
    Match(Lexicon::ELIF);
    auto cond = ParseExpr();
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
    std::unique_ptr<ASTs::Expr> condExpr;
    if(InstructIs(Lexicons::Instruct::Type_Loop))
    {
        auto instruct = GetInstruct();
        condExpr = std::make_unique<ASTs::InstructExpr>(instruct->type, instruct->value);
        Next();
    }
    else
    {
        // HOIL only support while loops
        condExpr = std::make_unique<ASTs::EmptyExpr>(0, 0);
    
        Match(Lexicon::LOOP);
    
        if(LexemeIs(Lexicon::UNTIL))
        {
            Next();
            condExpr = std::move(ParseExpr());
        }
        Match(Lexicon::NEWLINE);
    }


    std::unique_ptr<ASTs::Stmt> body = ParseStmt();

    return std::make_unique<ASTs::WhileStmt>(condExpr.release(), body.release(), LineNo(), CharNo());
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

    Match(Lexicon::NEWLINE);
    return stmt;
}

std::unique_ptr<ASTs::Stmt> Parser::ParseReturnStmt()
{
    Match(Lexicon::RETURN);

    std::unique_ptr<ASTs::Expr> expr = std::make_unique<ASTs::EmptyExpr>(LineNo(), CharNo());

    if(!LexemeIs(Lexicon::NEWLINE))
    {
        expr = ParseExpr();
    }

    Match(Lexicon::NEWLINE);

    return std::make_unique<ASTs::ReturnStmt>(expr.release(), LineNo(), CharNo());
}

std::unique_ptr<ASTs::Stmt> Parser::ParseCompoundStmt()
{
    if(!Match(Lexicon::OCURLY))
    {
        return std::make_unique<ASTs::ErrorStmt>(LineNo(), CharNo());
    }

    std::unique_ptr<ASTs::List> list = std::make_unique<ASTs::EmptyBlockList>();

    while(LexemeIs(Lexicon::NEWLINE))
    {
        Next(); // Trim new lines in case of empty compound stmt
    }

    if(!LexemeIs(Lexicon::CCURLY))
    {
        list = ParseItemList();
    }

    Match(Lexicon::CCURLY);
    Match(Lexicon::NEWLINE);
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

    // First set of all stmts
    if(
        LexemeIs(Lexicon::IDENTIFIER) ||
        LexemeIs(Lexicon::IF) ||
        InstructIs(Instruct::Type_Conditional) ||
        InstructIs(Instruct::Type_Expr) ||
        LexemeIs(Lexicon::LOOP) ||
        InstructIs(Instruct::Type_Loop) ||
        LexemeIs(Lexicon::BREAK) ||
        LexemeIs(Lexicon::CONTINUE) ||
        LexemeIs(Lexicon::OCURLY) ||
        LexemeIs(Lexicon::GREATER) ||
        LexemeIs(Lexicon::DEFINE) ||
        LexemeIs(Lexicon::CALL) ||
        LexemeIs(Lexicon::RETURN))
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
    // Hybrid between words and symbols. Translate word to symbol
    std::string spelling = currentLexicon->spelling;

    if(LexemeIs(Lexicon::IS))
    {
        Next();

        if(LexemeIs(Lexicon::NOT_KWD))
        {
            Next();
            spelling = "!=";
        }
        else
        {
            spelling = "==";
        }


    }
    else if(LexemeIs(Lexicon::NOT_KWD))
    {
        Next();

        if(LexemeIs(Lexicon::EQUAL_KWD))
        {
            Next();
            spelling = "!=";
        }
        else
        {
            spelling = "!";
        }

    }
    else if(LexemeIs(Lexicon::EQUAL_KWD))
    {
        spelling = "==";
    }
    else
    {
        Next(); // Symbol keyword.
    }


    auto op = std::make_unique<ASTs::Operator>(spelling, LineNo(), CharNo());

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
