#ifndef PARSER_H
#define PARSER_H

#include <memory>
#include <exception>
#include <iostream>
#include <cmath>

#include "Scanner.h"
#include "Token.h"
#include "Queue.h"

class UnexpectedToken : public std::exception
{
private:
    Token token;
    Token::Type type;

public:
    UnexpectedToken(Token to, Token::Type ty) :
        token(to),
        type(ty)
    {}

    const char* what() const throw()
    {
        return "Unexpected Token";
    }
};

class Parser
{
private:
    Scanner m_scanner;
    Queue<Token> m_buffer;
    std::shared_ptr<Token> m_currentToken;
    bool m_eof;

    inline void readTokens()
    {
        if (!m_eof)
        {
            if (m_buffer.length() < 10)
            {
                while ((m_buffer.length() < 40) && !(m_scanner.atEnd()))
                {
                    Token t = m_scanner.nextToken();
                    std::wcout<<t.name()<<" : "<<t.value()<<"\n";
                    m_buffer<<t;
                }
                if (m_scanner.atEnd())
                {
                    m_eof = true;
                }
            }
        }
    }

    inline void nextToken()
    {
        m_currentToken = std::make_shared<Token>(m_buffer.get());
        readTokens();
    }

    inline void eat(Token::Type tokenType)
    {
        if ((*m_currentToken) == tokenType)
        {
            nextToken();
            return;
        }
        throw UnexpectedToken((*m_currentToken), tokenType);
    }

    inline double factor()
    {
        std::shared_ptr<Token> f = m_currentToken;
        if ((*f) == Token::Type::LParen)
        {
            eat(Token::Type::LParen);
            double result = expression();
            eat(Token::Type::RParen);
            return result;
        }
        eat(Token::Type::Number);
        return f->toNumber();
    }

    inline double exponent()
    {
        double result = factor();

        while ((*m_currentToken) == Token::Type::OperatorExp)
        {
            std::shared_ptr<Token> t = m_currentToken;
            eat(Token::Type::OperatorExp);
            result = pow(result, factor());
        }
        return result;
    }

    inline double term()
    {
        double result = exponent();

        while ((*m_currentToken) == Token::Type::OperatorMul || (*m_currentToken) == Token::Type::OperatorDiv)
        {
            std::shared_ptr<Token> t = m_currentToken;
            if ((*t) == Token::Type::OperatorMul)
            {
                eat(Token::Type::OperatorMul);
                result *= exponent();
            }
            else if ((*t) == Token::Type::OperatorDiv)
            {
                eat(Token::Type::OperatorDiv);
                result /= exponent();
            }
        }
        return result;
    }

    inline double expression()
    {
        double result = term();

        while ((*m_currentToken) == Token::Type::OperatorPlus || (*m_currentToken) == Token::Type::OperatorMinus)
        {
            std::shared_ptr<Token> t = m_currentToken;
            if ((*t) == Token::Type::OperatorPlus)
            {
                eat(Token::Type::OperatorPlus);
                result += term();
            }
            else if ((*t) == Token::Type::OperatorMinus)
            {
                eat(Token::Type::OperatorMinus);
                result -= term();
            }
        }
        return result;
    }

public:
    Parser(const char* input) :
        m_scanner(input),
        m_currentToken(nullptr),
        m_eof(false)
    {
        readTokens();
        nextToken();
    }

    void run()
    {
        std::wcout<<expression()<<"\n";
    }
};

#endif // PARSER_H
