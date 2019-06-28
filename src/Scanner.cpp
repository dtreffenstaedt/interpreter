#include "../include/Scanner.h"
#include <iostream>

Scanner::Scanner(const char* input) :
    m_char(EOF),
    m_eof(false),
    m_locale("en_US.UTF8")
{
    m_inStream.open(input);
    if (m_inStream)
    {
        m_inStream.imbue(m_locale);
        readCharacters();
        nextChar();
    }
}

Token Scanner::nextToken()
{
    skipSpaces();
    Position p = m_pos;
    if (atEnd())
    {
        return Token(p, Token::Type::End);
    }
    switch (m_char)
    {
    case '%':
        nextChar();
        return Token(p, Token::Type::OperatorModulo);
        break;
    case '*':
        nextChar();
        if ((m_char) == '=')
        {
            nextChar();
            return Token(p, Token::Type::OperatorMultAssign);
        }
        return Token(p, Token::Type::OperatorMult);
        break;
    case '+':
        nextChar();
        if ((m_char) == '=')
        {
            nextChar();
            return Token(p, Token::Type::OperatorAddAssign);
        }
        if ((m_char) == '+')
        {
            nextChar();
            return Token(p, Token::Type::OperatorIncrement);
        }
        return Token(p, Token::Type::OperatorPlus);
        break;
    case '-':
        nextChar();
        if ((m_char) == '=')
        {
            nextChar();
            return Token(p, Token::Type::OperatorSubAssign);
        }
        if ((m_char) == '-')
        {
            nextChar();
            return Token(p, Token::Type::OperatorDecrement);
        }
        return Token(p, Token::Type::OperatorMinus);
        break;
    case '^':
        nextChar();
        return Token(p, Token::Type::OperatorExp);
        break;
    case '!':
        nextChar();
        if (m_char == '=')
        {
            nextChar();
            return Token(p, Token::Type::OperatorNotEqual);
        }
        break;
    case '/':
        nextChar();
        if ((m_char) == '=')
        {
            nextChar();
            return Token(p, Token::Type::OperatorDivAssign);
        }
        if ((m_char) == '/')
        {
            gotoNextLine();
            return nextToken();
        }
        if (m_char == '*')
        {
            gotoCommentEnd();
            return nextToken();
        }
        return Token(p, Token::Type::OperatorDiv);
        break;
    case '#':
        gotoNextLine();
        return nextToken();
        break;
    case '(':
        nextChar();
        return Token(p, Token::Type::LParen);
        break;
    case ')':
        nextChar();
        return Token(p, Token::Type::RParen);
        break;
    case '{':
        nextChar();
        return Token(p, Token::Type::LBrace);
        break;
    case '}':
        nextChar();
        return Token(p, Token::Type::RBrace);
        break;
    case '[':
        nextChar();
        return Token(p, Token::Type::LBracket);
        break;
    case ']':
        nextChar();
        return Token(p, Token::Type::RBracket);
        break;
    case ';':
        nextChar();
        return Token(p, Token::Type::Semicolon);
        break;
    case ':':
        nextChar();
        if (m_char == ':')
        {
            nextChar();
            return Token(p, Token::Type::OperatorScopeResolution);
        }
        return Token(p, Token::Type::Colon);
        break;
    case ',':
        nextChar();
        return Token(p, Token::Type::Comma);
        break;
    case '.':
        nextChar();
        return Token(p, Token::Type::Period);
        break;
    case '=':
        nextChar();
        if ((m_char) == '=')
        {
            nextChar();
            return Token(p, Token::Type::OperatorEqual);
        }
        return Token(p, Token::Type::OperatorAssign);
        break;
    case '<':
        nextChar();
        if ((m_char) == '=')
        {
            nextChar();
            return Token(p, Token::Type::OperatorLessEqual);
        }
        return Token(p, Token::Type::OperatorLessThan);
        break;
    case '>':
        nextChar();
        if ((m_char) == '=')
        {
            nextChar();
            return Token(p, Token::Type::OperatorGreaterEqual);
        }
        return Token(p, Token::Type::OperatorGreaterThan);
        break;
    }
    std::wstring buf;

    if ((m_char) == '"')
    {
        nextChar();
        while (true)
        {
            if (atEnd())
            {
                return Token(p, Token::Type::UnexpectedEnd);
            }
            if ((m_char) == '\\')
            {
                nextChar();
                buf += m_char;
            }
            else if ((m_char) == '"')
            {
                nextChar();
                break;
            }
            buf += m_char;
            nextChar();
        }
        return Token(p, Token::Type::String, buf);
    }
    if ((m_char) == '\'')
    {
        nextChar();
        buf = (m_char);
        nextChar();
        if ((m_char) != '\'')
        {
            buf = m_char;
            return Token(p, Token::Type::Unexpected, buf);
        }
        nextChar();
        return Token(p, Token::Type::Character, buf);
    }
    if (isalpha(m_char, m_locale))
    {
        while (isalnum(m_char, m_locale) || (m_char) == '_')
        {
            if (atEnd())
            {
                return Token(p, Token::Type::UnexpectedEnd);
            }
            buf += (m_char);
            nextChar();
        }
        for (int i = 0; i < KeywordStrLen; i++)
        {
            if (buf == KeywordStr[i])
            {
                return Token(p, (Token::Type) i);
            }
        }
        return Token(p, Token::Type::Identifier, buf);
    }
    if (isdigit(m_char, m_locale))
    {
        bool isFloat = false;
        while (isdigit(m_char, m_locale) || (m_char) == '.')
        {
            if (atEnd())
            {
                return Token(p, Token::Type::UnexpectedEnd);
            }
            if ((m_char) == '.')
            {
                if (isFloat)
                {
                    nextChar();
                    break;
                }
                isFloat = true;
            }
            buf += (m_char);
            nextChar();
        }
        return Token(p, Token::Type::Number, buf);
    }
    buf = (m_char);
    nextChar();
    return Token(p, Token::Type::Unknown, buf);
}
