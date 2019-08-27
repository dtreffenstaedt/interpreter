#include "AST/Boolean.h"

#include <iostream>
#include <cmath>

#include "FunctionManager.h"

namespace AST
{
    Boolean::Boolean(std::shared_ptr<Token>(token), Position pos) :
        Base(Type::Boolean, pos),
        m_token(token),
        m_bool(token->toBoolean())
    {}

    Data Boolean::execute(std::shared_ptr<FunctionManager> fnManager, std::shared_ptr<VariableManager> varManager, Data d)
    {
        Data val;
        val.type = DataType::Boolean;
        val.t_bool = m_bool;
        return val;
    }

}
