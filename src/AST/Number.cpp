#include "AST/Number.h"

#include <iostream>
#include <cmath>

#include "FunctionManager.h"

namespace AST
{
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
