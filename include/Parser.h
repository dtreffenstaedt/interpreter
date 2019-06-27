#ifndef PARSER_H
#define PARSER_H

#include <memory>
#include <exception>
#include <iostream>
#include <cmath>
#include <codecvt>


#include "Scanner.h"
#include "Token.h"
#include "Queue.h"
#include "AST.h"

class UnexpectedToken : public std::exception
{
private:
    Token token;
    Token expected;

public:
    UnexpectedToken(Token to, Token exp) :
        token(to),
        expected(exp)
    {}

    void print()
    {
        std::wstring buf;
        buf = L"Unexpected Token: ";
        buf += token.name();
        buf += L" (expected:";
        buf += expected.name();
        buf += L")";
        buf += L"\n\tat ";
        buf += std::to_wstring(token.pos().row);
        buf += L":";
        buf += std::to_wstring(token.pos().col);
        buf += L"\n";
        std::wcerr<<buf;
    }

    const char* what() const throw()
    {
        std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;
        std::string buf;
        buf = "Unexpected Token: ";
        buf += converter.to_bytes(token.name());
        buf += "\n\tat ";
        buf += std::to_string(token.pos().row);
        buf += ":";
        buf += std::to_string(token.pos().col);
        buf += "\n";
        return buf.c_str();
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
        std::wcout<<m_currentToken->name()<<" : "<<m_currentToken->value()<<"\n";
        readTokens();
    }

    inline void eat(Token::Type tokenType)
    {
        if ((*m_currentToken) == tokenType)
        {
            nextToken();
            return;
        }
        throw UnexpectedToken((*m_currentToken), Token({1,1}, tokenType));
    }

    inline std::shared_ptr<AST> compountStatement()
    {
        eat(Token::Type::LBrace);
        std::shared_ptr<Compount> root = std::make_shared<Compount>(Compount());
        root->append(statement());
        while ((*m_currentToken) == Token::Type::Semicolon)
        {
            eat(Token::Type::Semicolon);
            if ((*m_currentToken) == Token::Type::RBrace)
            {
                break;
            }
            root->append(statement());
        }
        eat(Token::Type::RBrace);
        return root;
    }

    inline std::shared_ptr<AST> statement()
    {
        if ((*m_currentToken) == Token::Type::LBrace)
        {
            return compountStatement();
        }
        else if ((*m_currentToken) == Token::Type::Literal)
        {
            return assignment();
        }
        return std::make_shared<Empty>(Empty());
    }

    inline std::shared_ptr<AST> variable()
    {
       std::shared_ptr<AST> var = std::make_shared<Variable>(Variable(m_currentToken));
       eat(Token::Type::Literal);
       return var;
    }

    inline std::shared_ptr<AST> assignment()
    {
        std::shared_ptr<AST> var = variable();
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
        return std::make_shared<Assignment>(Assignment(var,t,expression()));
        std::shared_ptr<AST> right = variable();
    }

    inline std::shared_ptr<AST> factor()
    {
        std::shared_ptr<Token> f = m_currentToken;

        if ((*f) == Token::Type::Number)
        {
            eat(Token::Type::Number);
            return std::make_shared<Number>(Number(f));
        }
        else if ((*f) == Token::Type::OperatorPlus)
        {
            eat(Token::Type::OperatorPlus);
            std::shared_ptr<AST> result = std::make_shared<UnaryOperation>(UnaryOperation(f, factor()));
            return result;
        }
        if ((*f) == Token::Type::OperatorMinus)
        {
            eat(Token::Type::OperatorMinus);
            std::shared_ptr<AST> result = std::make_shared<UnaryOperation>(UnaryOperation(f, factor()));
            return result;
        }
        else if ((*f) == Token::Type::LParen)
        {
            eat(Token::Type::LParen);
            std::shared_ptr<AST> result = expression();
            eat(Token::Type::RParen);
            return result;
        }
        return variable();
    }

    inline std::shared_ptr<AST> exponent()
    {
        std::shared_ptr<AST> result = factor();

        while ((*m_currentToken) == Token::Type::OperatorExp)
        {
            std::shared_ptr<Token> t = m_currentToken;
            eat(Token::Type::OperatorExp);
            result = std::make_shared<BinaryOperation>(BinaryOperation(result, t, factor()));
        }
        return result;
    }

    inline std::shared_ptr<AST> term()
    {
        std::shared_ptr<AST> result = exponent();

        while ((*m_currentToken) == Token::Type::OperatorMul || (*m_currentToken) == Token::Type::OperatorDiv)
        {
            std::shared_ptr<Token> t = m_currentToken;
            if ((*t) == Token::Type::OperatorMul)
            {
                eat(Token::Type::OperatorMul);
            }
            else if ((*t) == Token::Type::OperatorDiv)
            {
                eat(Token::Type::OperatorDiv);
            }
            result = std::make_shared<BinaryOperation>(BinaryOperation(result, t, exponent()));
        }
        return result;
    }

    inline std::shared_ptr<AST> expression()
    {
        std::shared_ptr<AST> result = term();

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
            result = std::make_shared<BinaryOperation>(BinaryOperation(result, t, term()));
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

    std::shared_ptr<AST> parse()
    {
        std::shared_ptr<AST> result = statement();
        eat(Token::Type::End);
        return result;
    }
};

#endif // PARSER_H
