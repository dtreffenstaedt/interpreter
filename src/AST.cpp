#include "AST.h"

#include <iostream>
#include <cmath>

namespace AST
{
    Empty::Empty(Position pos) :
        Base(Type::Empty, pos)
    {}

    void Empty::print()
    {}

    Data Empty::execute(std::shared_ptr<VariableManager> varManager, Data d)
    {
        return Data();
    }

    BinaryOperation::BinaryOperation(std::shared_ptr<Base> left, std::shared_ptr<Token> token, std::shared_ptr<Base> right, Position pos) :
        Base(Type::BinaryOperation, pos),
        m_left(left),
        m_token(token),
        m_right(right)
    {}

    void BinaryOperation::print()
    {
        std::wcout<<L"BinOp(";
        m_left->print();
        std::wcout<<L" "<<m_token->name()<<L" ";
        m_right->print();
        std::wcout<<L")";
    }

    Data BinaryOperation::execute(std::shared_ptr<VariableManager> varManager, Data d)
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

    UnaryOperation::UnaryOperation(std::shared_ptr<Token> token, std::shared_ptr<Base> expression, Position pos) :
        Base(Type::UnaryOperation, pos),
        m_token(token),
        m_expression(expression)
    {}

    void UnaryOperation::print()
    {
        std::wcout<<L"(";
        std::wcout<<L" "<<m_token->name()<<L" ";
        m_expression->print();
        std::wcout<<L")";
    }

    Data UnaryOperation::execute(std::shared_ptr<VariableManager> varManager, Data d)
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

    Compound::Compound(Position pos) :
        Base(Type::Compound, pos)
    {}

    void Compound::append(std::shared_ptr<Base> statement)
    {
        m_statements.push_back(statement);
    }

    void Compound::print()
    {
        std::wcout<<L"Compound: \n";
        for (auto i = m_statements.begin(); i != m_statements.end(); ++i)
        {
            (*i)->print();
            std::wcout<<L"\n";
        }
        std::wcout<<L"/Compound\n";
    }

    Data Compound::execute(std::shared_ptr<VariableManager> varManager, Data d)
    {
        varManager->enterScope();
        for (auto i = m_statements.begin(); i != m_statements.end(); ++i)
        {
            (*i)->execute(varManager);
        }
        varManager->leaveScope();
        return Data();
    }

    Definition::Definition(std::shared_ptr<Token> type, std::shared_ptr<Base> variable, std::shared_ptr<Base> initialiser, Position pos) :
        Base(Type::Definition, pos),
        m_type(type),
        m_variable(variable),
        m_initialiser(initialiser)
    {}

    void Definition::print()
    {
        std::wcout<<m_type->name()<<L" ";
        m_variable->print();
        std::wcout<<" Define ";
        m_initialiser->print();
    }

    Data Definition::execute(std::shared_ptr<VariableManager> varManager, Data d)
    {
        Data def;
        def.type = Data::Type::Definition;
        m_variable->execute(varManager, def);
        m_variable->execute(varManager, m_initialiser->execute(varManager));
        return Data();
    }

    Assignment::Assignment(std::shared_ptr<Base> left, std::shared_ptr<Token> token, std::shared_ptr<Base> right, Position pos) :
        Base(Type::Assignment, pos),
        m_left(left),
        m_token(token),
        m_right(right)
    {}

    void Assignment::print()
    {
        std::wcout<<L"(";
        m_left->print();
        std::wcout<<L" "<<m_token->name()<<L" ";
        m_right->print();
        std::wcout<<L")";
    }

    Data Assignment::execute(std::shared_ptr<VariableManager> varManager, Data d)
    {
        return m_left->execute(varManager, m_right->execute(varManager));
    }

    Variable::Variable(std::shared_ptr<Token>(token), Position pos) :
        Base(Type::Variable, pos),
        m_token(token),
        m_name(token->value())
    {}

    void Variable::print()
    {
        std::wcout<<L"var: "<<m_token->value();
    }

    Data Variable::execute(std::shared_ptr<VariableManager> varManager, Data d)
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

    Number::Number(std::shared_ptr<Token>(token), Position pos) :
        Base(Type::Number, pos),
        m_token(token),
        m_number(token->toNumber())
    {}

     void Number::print()
    {
        std::wcout<<m_token->value();
    }

    Data Number::execute(std::shared_ptr<VariableManager> varManager, Data d)
    {
        Data val;
        val.type = Data::Type::Number;
        val.t_number = m_number;
        return val;
    }
}
