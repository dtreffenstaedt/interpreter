#include "AST/BinaryOperation.h"

#include <iostream>
#include <cmath>

#include "FunctionManager.h"

namespace AST
{
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
}
