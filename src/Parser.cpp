#include "Parser.h"

Parser::Parser(const char* input) :
    m_scanner(input),
    m_currentToken(nullptr),
    m_eof(false)
{
    readTokens();
    nextToken();
}

std::shared_ptr<AST::Base> Parser::parse()
{
    std::shared_ptr<AST::Compound> root = std::make_shared<AST::Compound>(AST::Compound(Position{1,1}));
    while ((*m_currentToken) != Token::Type::End)
    {
        root->append(statement());
    }
    eat(Token::Type::End);
    return root;
}

std::shared_ptr<AST::Base> Parser::compoundStatement()
{
    std::shared_ptr<AST::Compound> root = std::make_shared<AST::Compound>(AST::Compound(m_currentToken->pos()));
    eat(Token::Type::LBrace);
    while ((*m_currentToken) != Token::Type::RBrace)
    {
        root->append(statement());
    }
    eat(Token::Type::RBrace);
    return root;
}

std::shared_ptr<AST::Base> Parser::statement()
{
    if ((*m_currentToken) == Token::Type::LBrace)
    {
        return compoundStatement();
    }
    else if ((*m_currentToken) == Token::Type::Identifier)
    {
        if ((*peek()) == Token::Type::LParen)
        {
            std::shared_ptr<AST::Base> call = functionCall();
            eat(Token::Type::Semicolon);
            return call;
        }
        std::shared_ptr<AST::Base> assign = assignment();
        eat(Token::Type::Semicolon);
        return assign;
    }
    else if (
        (*m_currentToken) == Token::Type::KeywordQuantity ||
        (*m_currentToken) == Token::Type::KeywordReal ||
        (*m_currentToken) == Token::Type::KeywordInteger ||
        (*m_currentToken) == Token::Type::KeywordBool ||
        (*m_currentToken) == Token::Type::KeywordString ||
        (*m_currentToken) == Token::Type::KeywordList ||
        (*m_currentToken) == Token::Type::KeywordChar ||
        (*m_currentToken) == Token::Type::KeywordVoid)
    {
        return definition();
    }
    else if ((*m_currentToken) == Token::Type::KeywordReturn)
    {
        Position pos = m_currentToken->pos();
        eat(Token::Type::KeywordReturn);
        std::shared_ptr<AST::Base> statement = std::make_shared<AST::ReturnStatement>(expression(), pos);
        eat(Token::Type::Semicolon);
        return statement;
    }
    else if ((*m_currentToken) == Token::Type::KeywordPrint)
    {
        Position pos = m_currentToken->pos();
        eat(Token::Type::KeywordPrint);
        std::shared_ptr<AST::Base> statement = std::make_shared<AST::PrintStatement>(expression(), pos);
        eat(Token::Type::Semicolon);
        return statement;
    }
    return std::make_shared<AST::Empty>(AST::Empty(m_currentToken->pos()));
}

std::shared_ptr<AST::Base> Parser::definition(bool parameter)
{
    std::shared_ptr<Token> t = m_currentToken;
    if ((*m_currentToken) == Token::Type::KeywordQuantity)
    {
        eat(Token::Type::KeywordQuantity);
    }
    if ((*m_currentToken) == Token::Type::KeywordReal)
    {
        eat(Token::Type::KeywordReal);
    }
    if ((*m_currentToken) == Token::Type::KeywordInteger)
    {
        eat(Token::Type::KeywordInteger);
    }
    if ((*m_currentToken) == Token::Type::KeywordBool)
    {
        eat(Token::Type::KeywordBool);
    }
    if ((*m_currentToken) == Token::Type::KeywordString)
    {
        eat(Token::Type::KeywordString);
    }
    if ((*m_currentToken) == Token::Type::KeywordChar)
    {
        eat(Token::Type::KeywordChar);
    }
    std::shared_ptr<Token> name = m_currentToken;
    eat(Token::Type::Identifier);
    if ((*m_currentToken) == Token::Type::LParen)
    {
        eat(Token::Type::LParen);
        std::shared_ptr<AST::FunctionDefinition> def = std::make_shared<AST::FunctionDefinition>(AST::FunctionDefinition(t, name, t->pos()));
        while (
        (*m_currentToken) == Token::Type::KeywordQuantity ||
        (*m_currentToken) == Token::Type::KeywordReal ||
        (*m_currentToken) == Token::Type::KeywordInteger ||
        (*m_currentToken) == Token::Type::KeywordBool ||
        (*m_currentToken) == Token::Type::KeywordString ||
        (*m_currentToken) == Token::Type::KeywordList ||
        (*m_currentToken) == Token::Type::KeywordChar ||
        (*m_currentToken) == Token::Type::KeywordVoid)
        {
            def->addParam(std::static_pointer_cast<AST::VariableDefinition>(definition(true)));
            if ((*m_currentToken) == Token::Type::RParen)
            {
                break;
            }
            eat(Token::Type::Comma);
        }
        eat(Token::Type::RParen);
        
        def->setImplementation(std::static_pointer_cast<AST::Compound>(compoundStatement()));
        return def;
    }
    else if ((*m_currentToken) == Token::Type::OperatorAssign)
    {
        eat(Token::Type::OperatorAssign);
        std::shared_ptr<AST::VariableDefinition> def = std::make_shared<AST::VariableDefinition>(
            AST::VariableDefinition(
                t,
                std::make_shared<AST::Variable>(AST::Variable(name, name->pos())),
                expression(),
                t->pos()
            )
        );

        if (!parameter)
        {
            eat(Token::Type::Semicolon);
        }

        return def;
    }
    else
    {
        std::shared_ptr<AST::VariableDefinition> def = std::make_shared<AST::VariableDefinition>(
            AST::VariableDefinition(
                t,
                std::make_shared<AST::Variable>(AST::Variable(name, name->pos())),
                std::make_shared<AST::Empty>(AST::Empty(name->pos())),
                t->pos()
            )
        );

        if (!parameter)
        {
            eat(Token::Type::Semicolon);
        }

        return def;
    }
}

std::shared_ptr<AST::Base> Parser::identifier()
{
    if ((*peek()) == Token::Type::LParen)
    {
        return functionCall();
    }
    return variable();
}

std::shared_ptr<AST::Base> Parser::functionCall()
{
    std::shared_ptr<AST::FunctionCall> fn = std::make_shared<AST::FunctionCall>(AST::FunctionCall(m_currentToken, m_currentToken->pos()));
    eat(Token::Type::Identifier);
    eat(Token::Type::LParen);
    while ((*m_currentToken) != Token::Type::RParen)
    {
        fn->addParam(expression());
        if ((*m_currentToken) == Token::Type::RParen)
        {
            break;
        }
        eat(Token::Type::Comma);
    }
    eat(Token::Type::RParen);
    return fn;
}

std::shared_ptr<AST::Base> Parser::variable()
{
    std::shared_ptr<AST::Base> var = std::make_shared<AST::Variable>(AST::Variable(m_currentToken, m_currentToken->pos()));
    eat(Token::Type::Identifier);
    return var;
}

std::shared_ptr<AST::Base> Parser::assignment()
{
    std::shared_ptr<AST::Base> var = variable();
    std::shared_ptr<Token> t = m_currentToken;
    if ((*t) == Token::Type::OperatorAssign)
    {
        eat(Token::Type::OperatorAssign);
    }
    else if ((*t) == Token::Type::OperatorAddAssign)
    {
        eat(Token::Type::OperatorAddAssign);
    }
    else if ((*t) == Token::Type::OperatorSubAssign)
    {
        eat(Token::Type::OperatorSubAssign);
    }
    else if ((*t) == Token::Type::OperatorMultAssign)
    {
        eat(Token::Type::OperatorMultAssign);
    }
    else if ((*t) == Token::Type::OperatorDivAssign)
    {
        eat(Token::Type::OperatorDivAssign);
    }
    return std::make_shared<AST::Assignment>(AST::Assignment(var,t,expression(), t->pos()));
}

std::shared_ptr<AST::Base> Parser::factor()
{
    std::shared_ptr<Token> f = m_currentToken;

    if ((*f) == Token::Type::Real)
    {
        eat(Token::Type::Real);
        return std::make_shared<AST::Real>(AST::Real(f, f->pos()));
    }
    else if ((*f) == Token::Type::Integer)
    {
        eat(Token::Type::Integer);
        return std::make_shared<AST::Integer>(AST::Integer(f, f->pos()));
    }
    else if ((*f) == Token::Type::OperatorPlus)
    {
        eat(Token::Type::OperatorPlus);
        std::shared_ptr<AST::Base> result = std::make_shared<AST::UnaryOperation>(AST::UnaryOperation(f, factor(), f->pos()));
        return result;
    }
    if ((*f) == Token::Type::OperatorMinus)
    {
        eat(Token::Type::OperatorMinus);
        std::shared_ptr<AST::Base> result = std::make_shared<AST::UnaryOperation>(AST::UnaryOperation(f, factor(), f->pos()));
        return result;
    }
    else if ((*f) == Token::Type::LParen)
    {
        eat(Token::Type::LParen);
        std::shared_ptr<AST::Base> result = expression();
        eat(Token::Type::RParen);
        return result;
    }
    return identifier();
}

std::shared_ptr<AST::Base> Parser::exponent()
{
    std::shared_ptr<AST::Base> result = factor();

    while ((*m_currentToken) == Token::Type::OperatorExp)
    {
        std::shared_ptr<Token> t = m_currentToken;
        eat(Token::Type::OperatorExp);
        result = std::make_shared<AST::BinaryOperation>(AST::BinaryOperation(result, t, factor(), t->pos()));
    }
    return result;
}

std::shared_ptr<AST::Base> Parser::term()
{
    if ((*m_currentToken) == Token::Type::String)
    {
        std::shared_ptr<AST::String> str = std::make_shared<AST::String>(AST::String(m_currentToken, m_currentToken->pos()));
        eat(Token::Type::String);
        return str;
    }
    if ((*m_currentToken) == Token::Type::Character)
    {
        std::shared_ptr<AST::Character> c = std::make_shared<AST::Character>(AST::Character(m_currentToken, m_currentToken->pos()));
        eat(Token::Type::Character);
        return c;
    }
    std::shared_ptr<AST::Base> result = exponent();

    while ((*m_currentToken) == Token::Type::OperatorMult || (*m_currentToken) == Token::Type::OperatorDiv)
    {
        std::shared_ptr<Token> t = m_currentToken;
        if ((*t) == Token::Type::OperatorMult)
        {
            eat(Token::Type::OperatorMult);
        }
        else if ((*t) == Token::Type::OperatorDiv)
        {
            eat(Token::Type::OperatorDiv);
        }
        result = std::make_shared<AST::BinaryOperation>(AST::BinaryOperation(result, t, exponent(), t->pos()));
    }
    return result;
}

std::shared_ptr<AST::Base> Parser::expression()
{
    if ((*m_currentToken) == Token::Type::KeywordTrue)
    {
        std::shared_ptr<AST::Boolean> b = std::make_shared<AST::Boolean>(AST::Boolean(m_currentToken, m_currentToken->pos()));
        eat(Token::Type::KeywordTrue);
        return b;
    }
    if ((*m_currentToken) == Token::Type::KeywordFalse)
    {
        std::shared_ptr<AST::Boolean> b = std::make_shared<AST::Boolean>(AST::Boolean(m_currentToken, m_currentToken->pos()));
        eat(Token::Type::KeywordFalse);
        return b;
    }
    std::shared_ptr<AST::Base> result = term();

    while ((*m_currentToken) == Token::Type::OperatorPlus || (*m_currentToken) == Token::Type::OperatorMinus)
    {
        std::shared_ptr<Token> t = m_currentToken;
        if ((*t) == Token::Type::OperatorPlus)
        {
            eat(Token::Type::OperatorPlus);
        }
        else if ((*t) == Token::Type::OperatorMinus)
        {
            eat(Token::Type::OperatorMinus);
        }
        result = std::make_shared<AST::BinaryOperation>(AST::BinaryOperation(result, t, term(), t->pos()));
    }
    return result;
}
