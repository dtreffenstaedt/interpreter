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
        Data left = m_left->execute(fnManager, varManager);
        Data right = m_right->execute(fnManager, varManager);

        Data val;

        if (((left.type == DataType::String || left.type == DataType::Character) && (right.type == DataType::String || right.type == DataType::Character)) && ((*m_token) == Token::Type::OperatorPlus))
        {
            val.type = DataType::String;

            val.t_string = (left.type==DataType::String)?left.t_string:std::wstring(1, left.t_char);
            val.t_string.append((right.type==DataType::String)?right.t_string:std::wstring(1, right.t_char));

            return val;
        }

        val.type = left.type;
        if ((left.type != DataType::Integer && left.type != DataType::Real) || (right.type != DataType::Integer && right.type != DataType::Real))
        {
            throw WrongType();
            return Data();
        }
        if ((*m_token) == Token::Type::OperatorMult)
        {
            if (left.type == DataType::Integer)
            {
                val.t_int = left.t_int * ((right.type==DataType::Integer)?right.t_int:right.t_real);
            }
            else
            {
                val.t_real = left.t_real * ((right.type==DataType::Integer)?right.t_int:right.t_real);
            }
            return val;
        }
        if ((*m_token) == Token::Type::OperatorDiv)
        {
            if (left.type == DataType::Integer)
            {
                val.t_int = left.t_int / ((right.type==DataType::Integer)?right.t_int:right.t_real);
            }
            else
            {
                val.t_real = left.t_real / ((right.type==DataType::Integer)?right.t_int:right.t_real);
            }
            return val;
        }
        if ((*m_token) == Token::Type::OperatorPlus)
        {
            if (left.type == DataType::Integer)
            {
                val.t_int = left.t_int + ((right.type==DataType::Integer)?right.t_int:right.t_real);
            }
            else
            {
                val.t_real = left.t_real + ((right.type==DataType::Integer)?right.t_int:right.t_real);
            }
            return val;
        }
        if ((*m_token) == Token::Type::OperatorMinus)
        {
            if (left.type == DataType::Integer)
            {
                val.t_int = left.t_int - ((right.type==DataType::Integer)?right.t_int:right.t_real);
            }
            else
            {
                val.t_real = left.t_real - ((right.type==DataType::Integer)?right.t_int:right.t_real);
            }
            return val;
        }
        if ((*m_token) == Token::Type::OperatorExp)
        {
            if (left.type == DataType::Integer)
            {
                val.t_int = pow(left.t_int, ((right.type==DataType::Integer)?right.t_int:right.t_real));
            }
            else
            {
                val.t_real = pow(left.t_real, ((right.type==DataType::Integer)?right.t_int:right.t_real));
            }
            return val;
        }
        return Data();
    }
}
