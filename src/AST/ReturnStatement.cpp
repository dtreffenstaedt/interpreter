#include "AST/ReturnStatement.h"

#include <iostream>
#include <cmath>

#include "FunctionManager.h"

namespace AST
{
    ReturnStatement::ReturnStatement(std::shared_ptr<Base> expression, Position pos) :
        Base(Type::ReturnStatement, pos),
        m_expression(expression)
    {}

    Data ReturnStatement::execute(std::shared_ptr<FunctionManager> fnManager, std::shared_ptr<VariableManager> varManager, Data d)
    {
        return m_expression->execute(fnManager, varManager);
    }

}
