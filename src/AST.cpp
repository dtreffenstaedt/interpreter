#include "AST.h"

#include <iostream>
#include <cmath>

#include "FunctionManager.h"

namespace AST
{
    Empty::Empty(Position pos) :
        Base(Type::Empty, pos)
    {}

    Data Empty::execute(std::shared_ptr<FunctionManager> fnManager, std::shared_ptr<VariableManager> varManager, Data d)
    {
        return Data();
    }

    BinaryOperation::BinaryOperation(std::shared_ptr<Base> left, std::shared_ptr<Token> token, std::shared_ptr<Base> right, Position pos) :
        Base(Type::BinaryOperation, pos),
        m_left(left),
        m_token(token),
        m_right(right)
    {}

    Data BinaryOperation::execute(std::shared_ptr<FunctionManager> fnManager, std::shared_ptr<VariableManager> varManager, Data d)
    {
        Data val;
        val.type = DataType::Number;

        Data left = m_left->execute(fnManager, varManager);
        Data right = m_right->execute(fnManager, varManager);
        if (left.type != DataType::Number || right.type != DataType::Number)
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

    Data UnaryOperation::execute(std::shared_ptr<FunctionManager> fnManager, std::shared_ptr<VariableManager> varManager, Data d)
    {
        Data val;
        val.type = DataType::Number;
        if ((*m_token) == Token::Type::OperatorMinus)
        {
            Data expr = m_expression->execute(fnManager, varManager);
            if (expr.type != DataType::Number)
            {
                return Data();
            }
            val.t_number = - expr.t_number;
            return val;
        }
        return m_expression->execute(fnManager, varManager);
    }

    ReturnStatement::ReturnStatement(std::shared_ptr<Base> expression, Position pos) :
        Base(Type::ReturnStatement, pos),
        m_expression(expression)
    {}

    Data ReturnStatement::execute(std::shared_ptr<FunctionManager> fnManager, std::shared_ptr<VariableManager> varManager, Data d)
    {
        return m_expression->execute(fnManager, varManager);
    }

    Compound::Compound(Position pos) :
        Base(Type::Compound, pos)
    {}

    void Compound::append(std::shared_ptr<Base> statement)
    {
        m_statements.push_back(statement);
    }

    Data Compound::execute(std::shared_ptr<FunctionManager> fnManager, std::shared_ptr<VariableManager> varManager, Data d)
    {
        varManager->enterScope();
        fnManager->enterScope();
        Data ret;
        for (auto i = m_statements.begin(); i != m_statements.end(); ++i)
        {
            if ((*i)->type == Base::Type::ReturnStatement)
            {
                ret = (*i)->execute(fnManager, varManager);
                std::wcout<<"Returning\n";
                break;
            }
            else
            {
                (*i)->execute(fnManager, varManager);
            }
        }
        varManager->leaveScope();
        fnManager->leaveScope();
        return ret;
    }

        FunctionCall::FunctionCall(std::shared_ptr<Token> token, Position pos) :
            Base(Type::FunctionCall, pos),
            m_token(token)
        {}

        void FunctionCall::addParam(std::shared_ptr<Base> parameter)
        {
            m_parameters.push_back(parameter);
        }

        Data FunctionCall::execute(std::shared_ptr<FunctionManager> fnManager, std::shared_ptr<VariableManager> varManager, Data d)
        {
            return fnManager->execute(m_token->value(), varManager, fnManager, m_parameters);
        }

        FunctionDefinition::FunctionDefinition(std::shared_ptr<Token> type, std::shared_ptr<Token> identifier, Position pos) :
        Base(Type::FunctionDefinition, pos),
        m_type(type),
        m_identifier(identifier)
        {}
        
        void FunctionDefinition::addParam(std::shared_ptr<VariableDefinition> parameter)
        {
            m_parameters.push_back(parameter);
        }

        void FunctionDefinition::setImplementation(std::shared_ptr<Compound> impl)
        {
            m_implementation = impl;
        }
        
        std::wstring FunctionDefinition::signature()
        {
            std::wstring sig = m_identifier->value();
            sig += L":";
            for (auto i = m_parameters.begin(); i != m_parameters.end(); i++)
            {
                std::shared_ptr<VariableDefinition> v = std::static_pointer_cast<VariableDefinition>(*i);
                sig += L" ";
                sig += v->type()->value();
            }
            return sig;
        }

        Data FunctionDefinition::execute(std::shared_ptr<FunctionManager> fnManager, std::shared_ptr<VariableManager> varManager, Data d)
        {
            fnManager->create(signature(), m_implementation, m_parameters, (DataType) (((int) m_type->type())-5));
            return Data();
        }


    VariableDefinition::VariableDefinition(std::shared_ptr<Token> type, std::shared_ptr<Base> variable, std::shared_ptr<Base> initialiser, Position pos) :
        Base(Type::VariableDefinition, pos),
        m_type(type),
        m_variable(variable),
        m_initialiser(initialiser)
    {}

    void VariableDefinition::setInitialiser(std::shared_ptr<Base> initialiser)
    {
        m_initialiser = initialiser;
    }

    std::shared_ptr<Token> VariableDefinition::type()
    {
        return m_type;
    }

    std::wstring VariableDefinition::name() const
    {
        return std::static_pointer_cast<Variable>(m_variable)->name();
    }

    Data VariableDefinition::execute(std::shared_ptr<FunctionManager> fnManager, std::shared_ptr<VariableManager> varManager, Data d)
    {
        Data def;
        def.action = Data::Action::Definition;
        m_variable->execute(fnManager, varManager, def);
        m_variable->execute(fnManager, varManager, m_initialiser->execute(fnManager, varManager));
        return Data();
    }

    Assignment::Assignment(std::shared_ptr<Base> left, std::shared_ptr<Token> token, std::shared_ptr<Base> right, Position pos) :
        Base(Type::Assignment, pos),
        m_left(left),
        m_token(token),
        m_right(right)
    {}

    Data Assignment::execute(std::shared_ptr<FunctionManager> fnManager, std::shared_ptr<VariableManager> varManager, Data d)
    {
        return m_left->execute(fnManager, varManager, m_right->execute(fnManager, varManager));
    }

    Variable::Variable(std::shared_ptr<Token>(token), Position pos) :
        Base(Type::Variable, pos),
        m_token(token),
        m_name(token->value())
    {}

    std::wstring Variable::name() const
    {
        return m_name;
    }

    Data Variable::execute(std::shared_ptr<FunctionManager> fnManager, std::shared_ptr<VariableManager> varManager, Data d)
    {
        if (d.action == Data::Action::Default)
        {
            Data val;
            val.type = DataType::Number;
            varManager->value(m_name, val.t_number);
            return val;
        }
        else if (d.action == Data::Action::Definition)
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

    Data Number::execute(std::shared_ptr<FunctionManager> fnManager, std::shared_ptr<VariableManager> varManager, Data d)
    {
        Data val;
        val.type = DataType::Number;
        val.t_number = m_number;
        return val;
    }
}
