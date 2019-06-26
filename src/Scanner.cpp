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
    if (atEnd())
    {
        return Token(Token::Type::End);
    }
    switch (m_char)
    {
    case '%':
        nextChar();
        return Token(Token::Type::OperatorModulo);
        break;
    case '*':
        nextChar();
        if ((m_char) == '=')
        {
            nextChar();
            return Token(Token::Type::OperatorMultAssign);
        }
        return Token(Token::Type::OperatorMul);
        break;
    case '+':
        nextChar();
        if ((m_char) == '=')
        {
            nextChar();
            return Token(Token::Type::OperatorAddAssign);
        }
        if ((m_char) == '+')
        {
            nextChar();
            return Token(Token::Type::OperatorIncrement);
        }
        return Token(Token::Type::OperatorPlus);
        break;
    case '-':
        nextChar();
        if ((m_char) == '=')
        {
            nextChar();
            return Token(Token::Type::OperatorSubAssign);
        }
        if ((m_char) == '-')
        {
            nextChar();
            return Token(Token::Type::OperatorDecrement);
        }
        return Token(Token::Type::OperatorMinus);
        break;
    case '^':
        nextChar();
        return Token(Token::Type::OperatorExp);
        break;
    case '!':
        nextChar();
        if (m_char == '=')
        {
            nextChar();
            return Token(Token::Type::OperatorNotEqual);
        }
        break;
    case '/':
        nextChar();
        if ((m_char) == '=')
        {
            nextChar();
            return Token(Token::Type::OperatorDivAssign);
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
        return Token(Token::Type::OperatorDiv);
        break;
    case '#':
        gotoNextLine();
        return nextToken();
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
        if (m_char == ':')
        {
            nextChar();
            return Token(Token::Type::OperatorScopeResolution);
        }
        return Token(Token::Type::Colon);
        break;
    case ',':
        nextChar();
        return Token(Token::Type::Comma);
        break;
    case '.':
        nextChar();
        return Token(Token::Type::Period);
        break;
    case '=':
        nextChar();
        if ((m_char) == '=')
        {
            nextChar();
            return Token(Token::Type::OperatorEqual);
        }
        return Token(Token::Type::OperatorAssign);
        break;
    case '<':
        nextChar();
        if ((m_char) == '=')
        {
            nextChar();
            return Token(Token::Type::OperatorLessEqual);
        }
        return Token(Token::Type::OperatorLessThan);
        break;
    case '>':
        nextChar();
        if ((m_char) == '=')
        {
            nextChar();
            return Token(Token::Type::OperatorGreaterEqual);
        }
        return Token(Token::Type::OperatorGreaterThan);
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
                return Token(Token::Type::UnexpectedEnd);
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
        return Token(Token::Type::String, buf);
    }
    if ((m_char) == '\'')
    {
        nextChar();
        buf = (m_char);
        nextChar();
        if ((m_char) != '\'')
        {
            buf = m_char;
            return Token(Token::Type::Unexpected, buf);
        }
        nextChar();
        return Token(Token::Type::Character, buf);
    }
    if (isalpha(m_char, m_locale))
    {
        while (isalnum(m_char, m_locale) || (m_char) == '_')
        {
            if (atEnd())
            {
                return Token(Token::Type::UnexpectedEnd);
            }
            buf += (m_char);
            nextChar();
        }
        for (int i = 0; i < KeywordStrLen; i++)
        {
            if (buf == KeywordStr[i])
            {
                return Token((Token::Type) i);
            }
        }
        return Token(Token::Type::Literal, buf);
    }
    if (isdigit(m_char, m_locale))
    {
        bool isFloat = false;
        while (isdigit(m_char, m_locale) || (m_char) == '.')
        {
            if (atEnd())
            {
                return Token(Token::Type::UnexpectedEnd);
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
        return Token(Token::Type::Number, buf);
    }
    buf = (m_char);
    nextChar();
    return Token(Token::Type::Unknown, buf);
}
