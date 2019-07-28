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
        std::shared_ptr<AST::Base> assign = assignment();
        eat(Token::Type::Semicolon);
        return assign;
    }
    else if (
        (*m_currentToken) == Token::Type::KeywordQuantity ||
        (*m_currentToken) == Token::Type::KeywordNumber ||
        (*m_currentToken) == Token::Type::KeywordBool ||
        (*m_currentToken) == Token::Type::KeywordString ||
        (*m_currentToken) == Token::Type::KeywordChar
    )
    {
        return definition();
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
    if ((*m_currentToken) == Token::Type::KeywordNumber)
    {
        eat(Token::Type::KeywordNumber);
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
    if ((*m_currentToken) == Token::Type::OperatorAssign)
    {
        eat(Token::Type::OperatorAssign);
        std::shared_ptr<AST::VariableDefinition> def = std::make_shared<AST::VariableDefinition>(AST::VariableDefinition(t, std::make_shared<AST::Variable>(AST::Variable(name, name->pos())), expression(), t->pos()));

        eat(Token::Type::Semicolon);

        return def;
    }
    else if ((*m_currentToken) == Token::Type::LParen)
    {
        if (parameter)
        {
            eat(Token::Type::Semicolon);
        }
        eat(Token::Type::LParen);
        std::shared_ptr<AST::FunctionDefinition> def = std::make_shared<AST::FunctionDefinition>(AST::FunctionDefinition(t, name, t->pos()));
        while ((*m_currentToken) >= Token::Type::KeywordQuantity && (*m_currentToken) <= Token::Type::KeywordList)
        {
            def->addParam(definition(true));
            eat(Token::Type::Comma);
        }
        eat(Token::Type::RParen);
        
        eat(Token::Type::LBrace);
        while ((*m_currentToken) != Token::Type::RBrace)
        {
            def->addStatement(statement());
        }
        eat(Token::Type::RBrace);

        return def;
    }
    else
    {
        std::shared_ptr<AST::VariableDefinition> def = std::make_shared<AST::VariableDefinition>(AST::VariableDefinition(t, std::make_shared<AST::Variable>(AST::Variable(name, name->pos())), std::make_shared<AST::Empty>(AST::Empty(name->pos())), t->pos()));

        eat(Token::Type::Semicolon);

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

    if ((*f) == Token::Type::Number)
    {
        eat(Token::Type::Number);
        return std::make_shared<AST::Number>(AST::Number(f, f->pos()));
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
