#include "AST/Real.h"

#include <iostream>
#include <cmath>

#include "FunctionManager.h"

namespace AST
{
    Real::Real(std::shared_ptr<Token>(token), Position pos) :
        Base(Type::Real, pos),
        m_token(token),
        m_number(token->toReal())
    {}

    Data Real::execute(std::shared_ptr<FunctionManager> fnManager, std::shared_ptr<VariableManager> varManager, Data d)
    {
        Data val;
        val.type = DataType::Real;
        val.t_real = m_number;
        return val;
    }

}
