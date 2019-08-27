#ifndef SCANNER_H
#define SCANNER_H

#include <fstream>
#include <locale>

#include "Token.h"
#include "Queue.h"

class Scanner
{
private:
    Queue<wchar_t> m_buffer;
    wchar_t m_char;

    bool m_eof;
    std::wifstream m_inStream;

    std::locale m_locale;

    Position m_pos;

public:
    Scanner(const char *input);

    Token nextToken();

    inline bool atEnd()
    {
        return m_buffer.empty();
    }

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
        while (isspace(m_char, m_locale))
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
                wchar_t c = 0;
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
        m_pos.col++;
        if (m_char == '\n')
        {
            m_pos.col = 1;
            m_pos.row++;
        }
        readCharacters();
    }

    inline wchar_t peek()
    {
        return m_buffer.peek();
    }
};

#endif // SCANNER_H
