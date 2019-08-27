#include "AST/Integer.h"

#include <iostream>
#include <cmath>

#include "FunctionManager.h"

namespace AST
{
    Integer::Integer(std::shared_ptr<Token>(token), Position pos) :
        Base(Type::Integer, pos),
        m_token(token),
        m_number(token->toInt())
    {}

    Data Integer::execute(std::shared_ptr<FunctionManager> fnManager, std::shared_ptr<VariableManager> varManager, Data d)
    {
        Data val;
        val.type = DataType::Integer;
        val.t_int = m_number;
        return val;
    }

}
