#ifndef EXCEPTIONS_H
#define EXCEPTIONS_H

#include <string>
#include <exception>
#include <iostream>

#include "Token.h"

class ErrorHandler
{
private:
    Position pos;
    std::wstring file;
};

class Error
{
public:
    std::wstring file;
    Position position;
    std::wstring description;
    std::wstring name;
    enum class Level
    {
        Error,
        Warning,
        Notice,
        Message
    } level = Level::Error;

    Error(std::wstring f, Position pos, std::wstring desc, std::wstring n, Level l) :
        file{f},
        position{pos},
        description{desc},
        name{n},
        level{l}
    {}

    const wchar_t* what()
    {
        std::wstring buf;
        buf += L"Error";
        buf += name;
        buf += L"in: ";
        buf += file;
        buf += L" ";
        buf += std::to_wstring(position.row);
        buf += L" ";
        buf += std::to_wstring(position.col);
        buf += L":\n\t";
        buf += description;
        return buf.c_str();
    }
};

class UnexpectedToken : public std::exception
{
private:
    Token token;
    Token expected;

public:
    UnexpectedToken(Token to, Token exp) :
        token(to),
        expected(exp)
    {}

    void print()
    {
        std::wstring buf;
        buf = L"Unexpected Token: ";
        buf += token.name();
        buf += L" (expected:";
        buf += expected.name();
        buf += L")";
        buf += L"\n\tat ";
        buf += std::to_wstring(token.pos().row);
        buf += L":";
        buf += std::to_wstring(token.pos().col);
        buf += L"\n";
        std::wcerr<<buf;
    }

    const char* what() const throw()
    {
        std::string buf;
        buf = "Unexpected Token: ";
        buf += "\n\tat ";
        buf += std::to_string(token.pos().row);
        buf += ":";
        buf += std::to_string(token.pos().col);
        buf += "\n";
        return buf.c_str();
    }
};

class FunctionUndefined : public std::exception
{
private:
    std::wstring signature;

public:
    FunctionUndefined(std::wstring n) :
        signature(n)
    {}

    void print()
    {
        std::wstring buf;
        buf = L"Function not defined: ";
        buf += signature;
        std::wcerr<<buf;
    }

    const char* what() const throw()
    {
        return "Function not defined.";
    }
};

class NoScope : public std::exception
{
public:
    NoScope()
    {}

    void print()
    {
        std::wcerr<<L"No scope defined.";;
    }

    const char* what() const throw()
    {
        return "No scope defined.";
    }
};

class WrongType : public std::exception
{
public:
    WrongType()
    {}

    void print()
    {
        std::wcerr<<L"Wrong DataType";;
    }

    const char* what() const throw()
    {
        return "Wrong DataType.";
    }
};

class FunctionExists : public std::exception
{
private:
    std::wstring signature;

public:
    FunctionExists(std::wstring n) :
        signature(n)
    {}

    void print()
    {
        std::wstring buf;
        buf = L"Function already exists: ";
        buf += signature;
        std::wcerr<<buf;
    }

    const char* what() const throw()
    {
        return "Function already exists.";
    }
};

class VariableUndefined : public std::exception
{
private:
    std::wstring name;

public:
    VariableUndefined(std::wstring n) :
        name(n)
    {}

    void print()
    {
        std::wstring buf;
        buf = L"Variable not defined: ";
        buf += name;
        std::wcerr<<buf;
    }

    const char* what() const throw()
    {
        return "Variable not defined.";
    }
};

class VariableExists : public std::exception
{
private:
    std::wstring name;

public:
    VariableExists(std::wstring n) :
        name(n)
    {}

    void print()
    {
        std::wstring buf;
        buf = L"Variable already exists: ";
        buf += name;
        std::wcerr<<buf;
    }

    const char* what() const throw()
    {
        return "Variable already exists.";
    }
};


#endif // EXCEPTIONS_H
