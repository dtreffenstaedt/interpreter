#ifndef AST_H
#define AST_H

#include <memory>
#include <iostream>
#include <list>

#include "Token.h"

class AST
{
public:
    virtual void traverse() = 0;
};

class Empty : public AST
{
public:
    explicit Empty()
    {}

    virtual void traverse()
    {}
};

class BinaryOperation : public AST
{
private:
    std::shared_ptr<AST> m_left;
    std::shared_ptr<Token> m_token;
    std::shared_ptr<AST> m_right;
public:
    BinaryOperation(std::shared_ptr<AST> left, std::shared_ptr<Token> token, std::shared_ptr<AST> right) :
        m_left(left),
        m_token(token),
        m_right(right)
    {}

    virtual void traverse()
    {
        std::wcout<<L"(";
        m_left->traverse();
        std::wcout<<L" "<<m_token->name()<<L" ";
        m_right->traverse();
        std::wcout<<L")";
    }
};

class UnaryOperation : public AST
{
private:
    std::shared_ptr<Token> m_token;
    std::shared_ptr<AST> m_expression;
public:
    UnaryOperation(std::shared_ptr<Token> token, std::shared_ptr<AST> expression) :
        m_token(token),
        m_expression(expression)
    {}

    virtual void traverse()
    {
        std::wcout<<L"(";
        std::wcout<<L" "<<m_token->name()<<L" ";
        m_expression->traverse();
        std::wcout<<L")";
    }
};

class Compount : public AST
{
private:
    std::list<std::shared_ptr<AST> > m_statements;
public:
    Compount()
    {}

    void append(std::shared_ptr<AST> statement)
    {
        m_statements.push_back(statement);
    }

    virtual void traverse()
    {
        std::wcout<<L"Compount: \n";
        for (auto i = m_statements.begin(); i != m_statements.end(); ++i)
        {
            (*i)->traverse();
            std::wcout<<L"\n";
        }
        std::wcout<<L"/Compount\n";
    }
};

class Assignment : public AST
{
private:
    std::shared_ptr<AST> m_left;
    std::shared_ptr<Token> m_token;
    std::shared_ptr<AST> m_right;
public:
    Assignment(std::shared_ptr<AST> left, std::shared_ptr<Token> token, std::shared_ptr<AST> right) :
        m_left(left),
        m_token(token),
        m_right(right)
    {}

    virtual void traverse()
    {
        std::wcout<<L"(";
        m_left->traverse();
        std::wcout<<L" "<<m_token->name()<<L" ";
        m_right->traverse();
        std::wcout<<L")";
    }
};

class Variable : public AST
{
private:
    std::shared_ptr<Token> m_token;
    std::wstring m_name;
public:
    Variable(std::shared_ptr<Token>(token)) :
        m_token(token),
        m_name(token->name())
    {}

    virtual  void traverse()
    {
        std::wcout<<m_token->value();
    }
};

class Number : public AST
{
private:
    std::shared_ptr<Token> m_token;
    double m_number;
public:
    Number(std::shared_ptr<Token>(token)) :
        m_token(token),
        m_number(token->toNumber())
    {}

    virtual  void traverse()
    {
        std::wcout<<m_token->value();
    }
};

#endif // AST_H
