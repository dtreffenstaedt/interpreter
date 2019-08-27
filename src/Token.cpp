#include "Token.h"

#include "Exceptions.h"

Token::Token(Position pos, Token::Type t, std::wstring value) :
    m_type(std::move(t)),
    m_value(std::move(value)),
    m_pos(pos)
{}

Token::Token(Position pos, Token::Type t) :
    m_type(t),
    m_pos(pos)
{}

Token::Type Token::type() const
{
    return m_type;
}

std::wstring Token::value() const
{
    return m_value;
}

double Token::toReal() const
{
    if (m_type != Type::Real)
    {
        throw WrongType();
    }
    return std::stod(m_value);
}

int64_t Token::toInt() const
{
    if (m_type != Type::Integer)
    {
        throw WrongType();
    }
    return std::stoll(m_value);
}

char Token::toCharacter() const
{
    if (m_type != Type::Character)
    {
        throw WrongType();
    }
    return m_value.c_str()[0];
}

bool Token::toBoolean() const
{
    if (m_type == Type::KeywordTrue)
    {
        return true;
    }
    if (m_type == Type::KeywordFalse)
    {
        return false;
    }

    throw WrongType();
}

std::wstring Token::name() const
{
    return TokenTypeStr[(int) m_type];
}

Position Token::pos() const
{
    return m_pos;
}

bool Token::operator==(const Token& other) const
{
    return (other.m_type == m_type && m_value == m_value);
}

bool Token::operator!=(const Token& other) const
{
    return (other.m_type != m_type || m_value != m_value);
}

bool Token::operator==(const Token::Type& t) const
{
    return (t == m_type);
}

bool Token::operator>=(const Type& t) const
{
    return (t >= m_type);
}

bool Token::operator<=(const Type& t) const
{
    return (t <= m_type);
}

bool Token::operator>(const Type& t) const
{
    return (t > m_type);
}

bool Token::operator<(const Type& t) const
{
    return (t < m_type);
}

bool Token::operator!=(const Token::Type& t) const
{
    return (t != m_type);
}
