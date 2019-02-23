#ifndef SCANNER_HPP
#define SCANNER_HPP

#include <string>
#include <iostream>

#include "Token.hpp"

class Scanner
{
private:
std::string m_input;
std::string::iterator m_it;
public:
    Scanner(const std::string& input);

    Token nextToken();

private:
    inline void gotoNextLine()
    {
        while ((*m_it) != '\n' && !atEnd())
        {
            nextChar();
        }
    }

    inline void skipSpaces()
    {
        while ((*m_it) == ' ' || (*m_it) == '\t' || (*m_it) == '\n' || (*m_it) == '\r')
        {
            nextChar();
        }
    }

    inline void nextChar()
    {
        ++m_it;
    }

    inline bool atEnd()
    {
        return m_it == m_input.end();
    }
};

#endif // SCANNER_HPP
