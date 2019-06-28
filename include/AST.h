#ifndef AST_H
#define AST_H

#include <memory>
#include <iostream>
#include <list>

#include "Token.h"
#include "VariableManager.h"

struct Data
{
    enum class Type
    {
//            Quantity,
        Number,
//            Boolean,
        String,
//            Character,
//            List
        Void
    } type = Type::Void;

//        Quantity t_quantity;
    double t_number;
    std::wstring t_string;
//        char t_char;
//        bool t_bool;
//        std::list<Variable> t_list;
};

namespace AST
{
    class Base
    {
    public:
        virtual void traverse() = 0;
        virtual Data execute(std::shared_ptr<VariableManager>) = 0;
    };

    class Empty : public Base
    {
    public:
        explicit Empty()
        {}

        virtual void traverse()
        {}

        virtual Data execute(std::shared_ptr<VariableManager> varManager)
        {
            return Data();
        }
    };

    class BinaryOperation : public Base
    {
    private:
        std::shared_ptr<Base> m_left;
        std::shared_ptr<Token> m_token;
        std::shared_ptr<Base> m_right;
    public:
        BinaryOperation(std::shared_ptr<Base> left, std::shared_ptr<Token> token, std::shared_ptr<Base> right) :
            m_left(left),
            m_token(token),
            m_right(right)
        {}

        virtual void traverse()
        {
            std::wcout<<L"BinOp(";
            m_left->traverse();
            std::wcout<<L" "<<m_token->name()<<L" ";
            m_right->traverse();
            std::wcout<<L")";
        }

        virtual Data execute(std::shared_ptr<VariableManager> varManager)
        {
            Data d;
            d.type = Data::Type::Number;
            Data left = m_left->execute(std::shared_ptr<VariableManager>␣varManager);
            Data right = m_right->execute(std::shared_ptr<VariableManager>␣varManager);
            if (left.type != Data::Type::Number || right.type != Data::Type::Number)
            {
                // TODO throw wrong operand Type.
                return Data();
            }
            if ((*m_token) == Token::Type::OperationMult)
            {
                d.t_number = left.t_number * right.t_number;
                return d;
            }
            if ((*m_token) == Token::Type::OperationDiv)
            {
                d.t_number = left.t_number / right.t_number;
                return d;
            }
            if ((*m_token) == Token::Type::OperationPlus)
            {
                d.t_number = left.t_number + right.t_number;
                return d;
            }
            if ((*m_token) == Token::Type::OperationMinus)
            {
                d.t_number = left.t_number - right.t_number;
                return d;
            }
            if ((*m_token) == Token::Type::OperationExp)
            {
                d.t_number = pow(left.t_number, right.t_number);
                return d;
            }
            return Data();
        }
    };

    class UnaryOperation : public Base
    {
    private:
        std::shared_ptr<Token> m_token;
        std::shared_ptr<Base> m_expression;
    public:
        UnaryOperation(std::shared_ptr<Token> token, std::shared_ptr<Base> expression) :
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

        virtual Data execute(std::shared_ptr<VariableManager> varManager)
        {
            Data d;
            d.type = Data::Type::Number;
            if ((*m_token) == Token::Type::OperatorMinus)
            {
                d.t_number = m_right->execute(std::shared_ptr<VariableManager>␣varManager)->t_number;
                return d;
            }
            return m_right->execute(std::shared_ptr<VariableManager>␣varManager);
        }
    };

    class Compount : public Base
    {
    private:
        std::list<std::shared_ptr<Base> > m_statements;
    public:
        Compount()
        {}

        void append(std::shared_ptr<Base> statement)
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

        virtual Data execute(std::shared_ptr<VariableManager>␣varManager)
        {
            for (auto i = m_statements.begin(); i != m_statements.end(); ++i)
            {
                (*i)->execute(std::shared_ptr<VariableManager>␣varManager);
            }
            return Data();
        }
    };

    class Definition : public Base
    {
    private:
        std::shared_ptr<Token> m_type;
        std::shared_ptr<Base> m_variable;
        std::shared_ptr<Base> m_initialiser;
    public:
        Definition(std::shared_ptr<Token> type, std::shared_ptr<Base> variable, std::shared_ptr<Base> initialiser) :
            m_type(type),
            m_variable(variable),
            m_initialiser(initialiser)
        {}

        virtual void traverse()
        {
            std::wcout<<m_type->name()<<L" ";
            m_variable->traverse();
            std::wcout<<" Define ";
            m_initialiser->traverse();
        }

        virtual Data execute(std::shared_ptr<VariableManager>␣varManager)
        {
            return Data();
        }
    };

    class Assignment : public Base
    {
    private:
        std::shared_ptr<Base> m_left;
        std::shared_ptr<Token> m_token;
        std::shared_ptr<Base> m_right;
    public:
        Assignment(std::shared_ptr<Base> left, std::shared_ptr<Token> token, std::shared_ptr<Base> right) :
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

        virtual Data execute(std::shared_ptr<VariableManager>␣varManager)
        {
            return Data();
        }
    };

    class Variable : public Base
    {
    private:
        std::shared_ptr<Token> m_token;
        std::wstring m_name;
    public:
        Variable(std::shared_ptr<Token>(token)) :
            m_token(token),
            m_name(token->name())
        {}

        virtual void traverse()
        {
            std::wcout<<L"var: "<<m_token->value();
        }

        virtual Data execute(std::shared_ptr<VariableManager>␣varManager)
        {
            Data d;
            d.type = Data::Type::String;
            d.t_string = m_name;
            return d;
        }
    };

    class Number : public Base
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

        virtual Data execute(std::shared_ptr<VariableManager>␣varManager)
        {
            return Data();
        }
    };
}
#endif // AST_H
