#ifndef AST_H
#define AST_H

#include <memory>

#include "Token.h"

class AST
{
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
};

#endif // AST_H
