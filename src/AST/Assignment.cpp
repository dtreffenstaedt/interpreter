#include "AST/Assignment.h"

#include <iostream>
#include <cmath>

#include "FunctionManager.h"

namespace AST
{
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

}
