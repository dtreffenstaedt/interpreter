#ifndef SCANNER_H
#define SCANNER_H

#include <fstream>
#include <cctype>

#include "Token.h"
#include "Queue.h"

class Scanner
{
private:
    Queue<char> m_buffer;
    char m_char;

    bool m_eof;
    std::ifstream m_inStream;

public:
    Scanner(const char *input);

    Token nextToken();

private:
    inline void gotoNextLine()
    {
        while (m_char != '\n' && !atEnd())
        {
            nextChar();
        }
    }

    inline void gotoCommentEnd()
    {
        while (!atEnd())
        {
            nextChar();
            if (m_char == '*')
            {
                nextChar();
                if (m_char == '/')
                {
                    nextChar();
                    break;
                }
            }
        }
    }

    inline void skipSpaces()
    {
        while (isspace(m_char))
        {
            nextChar();
        }
    }
    
    inline void readCharacters()
    {
        if (!m_eof)
        {
            if (m_buffer.length() < 10)
            {
                char c = 0;
                while ((m_buffer.length() < 40) && (m_inStream.get(c)))
                {
                    m_buffer<<c;
                }
                if (c == EOF)
                {
                    m_inStream.close();
                    m_eof = true;
                }
            }
        }
    }

    inline void nextChar()
    {
        m_char = m_buffer.get();
        readCharacters();
    }

    inline bool atEnd()
    {
        return m_buffer.empty();
    }
};

#endif // SCANNER_H
