#include "../include/Scanner.hpp"

Scanner::Scanner(const std::string& input) :
    m_input(input)
{
    m_it = m_input.begin();
}

Token Scanner::nextToken()
{
    skipSpaces();
    if (atEnd())
    {
        return Token(Token::Type::End);
    }
    switch (*m_it)
    {
    case '*':
        nextChar();
        if ((*m_it) == '=')
        {
            nextChar();
            return Token(Token::Type::OperatorMultAssign);
        }
        return Token(Token::Type::OperatorMul);
        break;
    case '+':
        nextChar();
        if ((*m_it) == '=')
        {
            nextChar();
            return Token(Token::Type::OperatorAddAssign);
        }
        return Token(Token::Type::OperatorPlus);
        break;
    case '-':
        nextChar();
        if ((*m_it) == '=')
        {
            nextChar();
            return Token(Token::Type::OperatorSubAssign);
        }
        return Token(Token::Type::OperatorMinus);
        break;
    case '^':
        nextChar();
        return Token(Token::Type::OperatorExp);
        break;
    case '/':
        nextChar();
        if ((*m_it) == '=')
        {
            nextChar();
            return Token(Token::Type::OperatorDivAssign);
        }
        if ((*m_it) == '/')
        {
            gotoNextLine();
            return Token(Token::Type::Comment);
        }
        return Token(Token::Type::OperatorDiv);
        break;
    case '(':
        nextChar();
        return Token(Token::Type::LParen);
        break;
    case ')':
        nextChar();
        return Token(Token::Type::RParen);
        break;
    case '{':
        nextChar();
        return Token(Token::Type::LBrace);
        break;
    case '}':
        nextChar();
        return Token(Token::Type::RBrace);
        break;
    case '[':
        nextChar();
        return Token(Token::Type::LBracket);
        break;
    case ']':
        nextChar();
        return Token(Token::Type::RBracket);
        break;
    case ';':
        nextChar();
        return Token(Token::Type::Semicolon);
        break;
    case ':':
        nextChar();
        return Token(Token::Type::Colon);
        break;
    case ',':
        nextChar();
        return Token(Token::Type::Comma);
        break;
    case '=':
        nextChar();
        if ((*m_it) == '=')
        {
            nextChar();
            return Token(Token::Type::OperatorEqual);
        }
        return Token(Token::Type::OperatorAssign);
        break;
    case '<':
        nextChar();
        if ((*m_it) == '=')
        {
            nextChar();
            return Token(Token::Type::OperatorLessEqual);
        }
        return Token(Token::Type::OperatorLessThan);
        break;
    case '>':
        nextChar();
        if ((*m_it) == '=')
        {
            nextChar();
            return Token(Token::Type::OperatorGreaterEqual);
        }
        return Token(Token::Type::OperatorGreaterThan);
        break;
    }
    std::string buf;

    if ((*m_it) == '"')
    {
        nextChar();
        while (true)
        {
            if (atEnd())
            {
                return Token(Token::Type::UnexpectedEnd);
            }
            if ((*m_it) == '\\')
            {
                nextChar();
                buf += *m_it;
            }
            else if ((*m_it) == '"')
            {
                nextChar();
                break;
            }
            buf += *m_it;
            nextChar();
        }
        return Token(Token::Type::String, buf);
    }
    if ((*m_it) == '\'')
    {
        nextChar();
        buf = (*m_it);
        nextChar();
        if ((*m_it) != '\'')
        {
            nextChar();
            return Token(Token::Type::Unexpected);
        }
        nextChar();
        return Token(Token::Type::Character, buf);
    }
    if (isalpha(*m_it))
    {
        while (isalnum(*m_it) || (*m_it) == '_')
        {
            if (atEnd())
            {
                return Token(Token::Type::UnexpectedEnd);
            }
            buf += (*m_it);
            nextChar();
        }
        return Token(Token::Type::Literal, buf);
    }
    if (isdigit(*m_it))
    {
        bool isFloat = false;
        while (isdigit(*m_it) || (*m_it) == '.')
        {
            if (atEnd())
            {
                return Token(Token::Type::UnexpectedEnd);
            }
            if ((*m_it) == '.')
            {
                if (isFloat)
                {
                    nextChar();
                    break;
                }
                isFloat = true;
            }
            buf += (*m_it);
            nextChar();
        }
        if (isFloat)
        {
            return Token(Token::Type::Float, buf);
        }
        return Token(Token::Type::Number, buf);
    }
    buf = (*m_it);
    nextChar();
    return Token(Token::Type::Unknown, buf);
}
