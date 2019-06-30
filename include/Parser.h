#ifndef PARSER_H
#define PARSER_H

#include <memory>
#include <iostream>
#include <cmath>

#include "Exceptions.h"
#include "Scanner.h"
#include "Token.h"
#include "Queue.h"
#include "AST.h"


class Parser
{
public:
    Parser(const char* input);

    std::shared_ptr<AST::Base> parse();

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

    std::shared_ptr<AST::Base> compountStatement();

    std::shared_ptr<AST::Base> statement();

    std::shared_ptr<AST::Base> definition();

    std::shared_ptr<AST::Base> variable();

    std::shared_ptr<AST::Base> assignment();

    std::shared_ptr<AST::Base> factor();

    std::shared_ptr<AST::Base> exponent();

    std::shared_ptr<AST::Base> term();

    std::shared_ptr<AST::Base> expression();
};

#endif // PARSER_H
