#ifndef PARSER_H
#define PARSER_H

#include <memory>
#include <exception>
#include <iostream>

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
    std::shared_ptr<Scanner> m_scanner;
    Queue<std::shared_ptr<Token> > m_buffer;
    std::shared_ptr<Token> m_currentToken;
    bool m_eof;

    void readTokens()
    {
        if (!m_eof)
        {
            if (m_buffer.length() < 10)
            {
                while ((m_buffer.length() < 40) && !(m_scanner.atEnd()))
                {
                    m_buffer<<m_scanner->nextToken();
                }
                if (m_scanner.atEnd())
                {
                    m_eof = true;
                }
            }
        }
    }

    void nextToken()
    {
        m_currentToken = m_buffer.get();
        readTokens();
    }

    void eat(Token::Type tokenType)
    {
        if ((*m_currentToken) == tokenType)
        {
            nextToken();
            return;
        }
        throw UnexpectedToken((*m_currentToken), tokenType);
    }

    double expression()
    {
        std::shared_ptr<Token> left = m_currentToken;
        eat(Token::Type::Number);

        std::shared_ptr<Token> op = m_currentToken;
        if (op == Token::Type::OperatorPlus)
        {
            eat(Token::Type::OperatorPlus);
        }
        else if (op == Token::Type::OperatorMinus)
        {
            eat(Token::Type::OperatorMinus);
        }
        else if (op == Token::Type::OperatorMul)
        {
            eat(Token::Type::OperatorMul);
        }
        else
        {
            eat(Token::Type::OperatorDiv);
        }

        std::shared_ptr<Token> right = m_currentToken;
        eat(Token::Type::Number);

        if (op == Token::Type::OperatorPlus)
        {
            (left->toNumber())+(right->toNumber());
        }
        else if (op == Token::Type::OperatorMinus)
        {
            (left->toNumber())-(right->toNumber());
        }
        else if (op == Token::Type::OperatorMul)
        {
            (left->toNumber())*(right->toNumber());
        }
        else if (op == Token::Type::OperatorDiv)
        {
            (left->toNumber())/(right->toNumber());
        }
    }

public:
    Parser(std::shared_ptr<Scanner> sc) :
        m_scanner(sc),
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
