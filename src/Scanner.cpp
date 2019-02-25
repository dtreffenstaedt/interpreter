#include "../include/Scanner.h"
#include <iostream>

Scanner::Scanner(const char* input) :
    m_char(EOF),
    m_eof(false)
{
    m_inStream.open(input);
    if (m_inStream)
    {
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
        if ((m_char) == '=')
        {
            nextChar();
            return Token(Token::Type::OperatorAssignXOR);
        }
        return Token(Token::Type::OperatorBitXOR);
        break;
    case '&':
        nextChar();
        if (m_char == '&')
        {
            nextChar();
            return Token(Token::Type::OperatorAnd);
        }
        if ((m_char) == '=')
        {
            nextChar();
            return Token(Token::Type::OperatorAssignAND);
        }
        return Token(Token::Type::OperatorBitAND);
        break;
    case '|':
        nextChar();
        if (m_char == '|')
        {
            nextChar();
            return Token(Token::Type::OperatorOr);
        }
        if ((m_char) == '=')
        {
            nextChar();
            return Token(Token::Type::OperatorAssignOR);
        }
        return Token(Token::Type::OperatorBitOR);
        break;
    case '~':
        nextChar();
        return Token(Token::Type::OperatorBitNOT);
        break;
    case '!':
        nextChar();
        if (m_char == '=')
        {
            nextChar();
            return Token(Token::Type::OperatorNotEqual);
        }
        return Token(Token::Type::OperatorNot);
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
            return Token(Token::Type::Comment);
        }
        if (m_char == '*')
        {
            gotoCommentEnd();
            return Token(Token::Type::Comment);
        }
        return Token(Token::Type::OperatorDiv);
        break;
    case '#':
        gotoNextLine();
        return Token(Token::Type::Comment);
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
        if ((m_char) == '<')
        {
            nextChar();
            return Token(Token::Type::OperatorLShift);
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
        if ((m_char) == '>')
        {
            nextChar();
            return Token(Token::Type::OperatorRShift);
        }
        return Token(Token::Type::OperatorGreaterThan);
        break;
    }
    std::string buf;

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
            nextChar();
            return Token(Token::Type::Unexpected);
        }
        nextChar();
        return Token(Token::Type::Character, buf);
    }
    if (isalpha(m_char))
    {
        while (isalnum(m_char) || (m_char) == '_')
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
    if (isdigit(m_char))
    {
        bool isFloat = false;
        while (isdigit(m_char) || (m_char) == '.')
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
        if (isFloat)
        {
            return Token(Token::Type::Float, buf);
        }
        return Token(Token::Type::Number, buf);
    }
    buf = (m_char);
    nextChar();
    return Token(Token::Type::Unknown, buf);
}
