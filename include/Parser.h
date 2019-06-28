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

    inline std::shared_ptr<AST::Base> compountStatement()
    {
        eat(Token::Type::LBrace);
        std::shared_ptr<AST::Compount> root = std::make_shared<AST::Compount>(AST::Compount());
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

    inline std::shared_ptr<AST::Base> statement()
    {
        if ((*m_currentToken) == Token::Type::LBrace)
        {
            return compountStatement();
        }
        else if ((*m_currentToken) == Token::Type::Identifier)
        {
            return assignment();
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
        return std::make_shared<AST::Empty>(AST::Empty());
    }

    inline std::shared_ptr<AST::Base> definition()
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
            return std::make_shared<AST::Definition>(AST::Definition(t, std::make_shared<AST::Variable>(AST::Variable(name)), expression()));
        }
        else
        {
            return std::make_shared<AST::Definition>(AST::Definition(t, std::make_shared<AST::Variable>(AST::Variable(name)), std::make_shared<AST::Empty>(AST::Empty())));
        }
    }

    inline std::shared_ptr<AST::Base> variable()
    {
       std::shared_ptr<AST::Base> var = std::make_shared<AST::Variable>(AST::Variable(m_currentToken));
       eat(Token::Type::Identifier);
       return var;
    }

    inline std::shared_ptr<AST::Base> assignment()
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
        return std::make_shared<AST::Assignment>(AST::Assignment(var,t,expression()));
    }

    inline std::shared_ptr<AST::Base> factor()
    {
        std::shared_ptr<Token> f = m_currentToken;

        if ((*f) == Token::Type::Number)
        {
            eat(Token::Type::Number);
            return std::make_shared<AST::Number>(AST::Number(f));
        }
        else if ((*f) == Token::Type::OperatorPlus)
        {
            eat(Token::Type::OperatorPlus);
            std::shared_ptr<AST::Base> result = std::make_shared<AST::UnaryOperation>(AST::UnaryOperation(f, factor()));
            return result;
        }
        if ((*f) == Token::Type::OperatorMinus)
        {
            eat(Token::Type::OperatorMinus);
            std::shared_ptr<AST::Base> result = std::make_shared<AST::UnaryOperation>(AST::UnaryOperation(f, factor()));
            return result;
        }
        else if ((*f) == Token::Type::LParen)
        {
            eat(Token::Type::LParen);
            std::shared_ptr<AST::Base> result = expression();
            eat(Token::Type::RParen);
            return result;
        }
        return variable();
    }

    inline std::shared_ptr<AST::Base> exponent()
    {
        std::shared_ptr<AST::Base> result = factor();

        while ((*m_currentToken) == Token::Type::OperatorExp)
        {
            std::shared_ptr<Token> t = m_currentToken;
            eat(Token::Type::OperatorExp);
            result = std::make_shared<AST::BinaryOperation>(AST::BinaryOperation(result, t, factor()));
        }
        return result;
    }

    inline std::shared_ptr<AST::Base> term()
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
            result = std::make_shared<AST::BinaryOperation>(AST::BinaryOperation(result, t, exponent()));
        }
        return result;
    }

    inline std::shared_ptr<AST::Base> expression()
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
            result = std::make_shared<AST::BinaryOperation>(AST::BinaryOperation(result, t, term()));
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

    std::shared_ptr<AST::Base> parse()
    {
        std::shared_ptr<AST::Base> result = statement();
        eat(Token::Type::End);
        return result;
    }
};

#endif // PARSER_H
