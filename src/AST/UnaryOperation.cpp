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


}
