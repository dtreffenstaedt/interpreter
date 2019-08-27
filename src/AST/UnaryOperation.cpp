#include "AST/UnaryOperation.h"

#include <iostream>
#include <cmath>

#include "FunctionManager.h"

namespace AST
{
    UnaryOperation::UnaryOperation(std::shared_ptr<Token> token, std::shared_ptr<Base> expression, Position pos) :
        Base(Type::UnaryOperation, pos),
        m_token(token),
        m_expression(expression)
    {}

    Data UnaryOperation::execute(std::shared_ptr<FunctionManager> fnManager, std::shared_ptr<VariableManager> varManager, Data d)
    {
        Data val;
        if ((*m_token) == Token::Type::OperatorMinus)
        {
            Data expr = m_expression->execute(fnManager, varManager);
            val.type = expr.type;
            if (expr.type != DataType::Integer && expr.type != DataType::Real)
            {
                throw WrongType();
                return Data();
            }
            val.t_int = - expr.t_int;
            val.t_real = - expr.t_real;
            return val;
        }
        return m_expression->execute(fnManager, varManager);
    }


}
