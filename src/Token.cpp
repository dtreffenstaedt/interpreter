#include "Token.h"

Token::Token(Token::Type t, std::string value) :
    m_type(t),
    m_value(value)
{}

Token::Token(Token::Type t) :
    m_type(t)
{}

Token::Type Token::type() const
{
    return m_type;
}

std::string Token::value() const
{
    return m_value;
}

int Token::toInt() const
{
    return std::stoi(m_value);
}

float Token::toFloat() const
{
    return std::stof(m_value);
}

std::string Token::name() const
{
    return TokenTypeStr[(int) m_type];
}

bool Token::operator==(Token &other) const
{
    return (other.m_type == m_type && m_value == m_value);
}

bool Token::operator!=(Token &other) const
{
    return (other.m_type != m_type || m_value != m_value);
}

bool Token::operator==(Token::Type t) const
{
    return (t == m_type);
}

bool Token::operator!=(Token::Type t) const
{
    return (t != m_type);
}
