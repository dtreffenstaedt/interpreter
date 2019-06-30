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
        Void,
        Definition
    } type = Type::Void;

//        Quantity t_quantity;
    double t_number = 0;
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
        enum class Type
        {
            Empty,
            BinaryOperation,
            UnaryOperation,
            Compount,
            Definition,
            Assignment,
            Variable,
            Number
        } type = Type::Empty;

        Position position;

        virtual void traverse() = 0;
        virtual Data execute(std::shared_ptr<VariableManager>, Data d = Data()) = 0;
        explicit Base(Type t = Type::Empty, Position pos = {1,1}) :
            type(t)
        {}
    };

    class Empty : public Base
    {
    public:
        explicit Empty(Position pos) :
            Base(Type::Empty, pos)
        {}

        virtual void traverse()
        {}

        virtual Data execute(std::shared_ptr<VariableManager> varManager, Data d)
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
        BinaryOperation(std::shared_ptr<Base> left, std::shared_ptr<Token> token, std::shared_ptr<Base> right, Position pos) :
            Base(Type::BinaryOperation, pos),
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

        virtual Data execute(std::shared_ptr<VariableManager> varManager, Data d)
        {
            Data val;
            val.type = Data::Type::Number;

            Data left = m_left->execute(varManager);
            Data right = m_right->execute(varManager);
            if (left.type != Data::Type::Number || right.type != Data::Type::Number)
            {
                // TODO throw wrong operand Type.
                return Data();
            }
            if ((*m_token) == Token::Type::OperatorMult)
            {
                val.t_number = left.t_number * right.t_number;
                return val;
            }
            if ((*m_token) == Token::Type::OperatorDiv)
            {
                val.t_number = left.t_number / right.t_number;
                return val;
            }
            if ((*m_token) == Token::Type::OperatorPlus)
            {
                val.t_number = left.t_number + right.t_number;
                return val;
            }
            if ((*m_token) == Token::Type::OperatorMinus)
            {
                val.t_number = left.t_number - right.t_number;
                return val;
            }
            if ((*m_token) == Token::Type::OperatorExp)
            {
                val.t_number = pow(left.t_number, right.t_number);
                return val;
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
        UnaryOperation(std::shared_ptr<Token> token, std::shared_ptr<Base> expression, Position pos) :
            Base(Type::UnaryOperation, pos),
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

        virtual Data execute(std::shared_ptr<VariableManager> varManager, Data d)
        {
            Data val;
            val.type = Data::Type::Number;
            if ((*m_token) == Token::Type::OperatorMinus)
            {
                Data expr = m_expression->execute(varManager);
                if (expr.type != Data::Type::Number)
                {
                    return Data();
                }
                val.t_number = - expr.t_number;
                return val;
            }
            return m_expression->execute(varManager);
        }
    };

    class Compount : public Base
    {
    private:
        std::list<std::shared_ptr<Base> > m_statements;
    public:
        Compount(Position pos) :
            Base(Type::Compount, pos)
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

        virtual Data execute(std::shared_ptr<VariableManager> varManager, Data d)
        {
            varManager->enterScope();
            for (auto i = m_statements.begin(); i != m_statements.end(); ++i)
            {
                (*i)->execute(varManager);
            }
            varManager->leaveScope();
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
        Definition(std::shared_ptr<Token> type, std::shared_ptr<Base> variable, std::shared_ptr<Base> initialiser, Position pos) :
            Base(Type::Definition, pos),
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

        virtual Data execute(std::shared_ptr<VariableManager> varManager, Data d)
        {
            Data def;
            def.type = Data::Type::Definition;
            m_variable->execute(varManager, def);
            m_variable->execute(varManager, m_initialiser->execute(varManager));
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
        Assignment(std::shared_ptr<Base> left, std::shared_ptr<Token> token, std::shared_ptr<Base> right, Position pos) :
            Base(Type::Assignment, pos),
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

        virtual Data execute(std::shared_ptr<VariableManager> varManager, Data d)
        {
            return m_left->execute(varManager, m_right->execute(varManager));
        }
    };

    class Variable : public Base
    {
    private:
        std::shared_ptr<Token> m_token;
        std::wstring m_name;
    public:
        Variable(std::shared_ptr<Token>(token), Position pos) :
            Base(Type::Variable, pos),
            m_token(token),
            m_name(token->value())
        {}

        virtual void traverse()
        {
            std::wcout<<L"var: "<<m_token->value();
        }

        virtual Data execute(std::shared_ptr<VariableManager> varManager, Data d)
        {
            if (d.type == Data::Type::Void)
            {
                Data val;
                val.type = Data::Type::Number;
                varManager->value(m_name, val.t_number);
                return val;
            }
            else if (d.type == Data::Type::Definition)
            {
                varManager->create(m_name);
                return Data();
            }
            varManager->assign(m_name, d.t_number);
            return Data();
        }
    };

    class Number : public Base
    {
    private:
        std::shared_ptr<Token> m_token;
        double m_number;
    public:
        Number(std::shared_ptr<Token>(token), Position pos) :
            Base(Type::Number, pos),
            m_token(token),
            m_number(token->toNumber())
        {}

        virtual  void traverse()
        {
            std::wcout<<m_token->value();
        }

        virtual Data execute(std::shared_ptr<VariableManager> varManager, Data d)
        {
            Data val;
            val.type = Data::Type::Number;
            val.t_number = m_number;
            return val;
        }
    };
}
#endif // AST_H
