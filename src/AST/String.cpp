#include "AST/String.h"

#include <iostream>

#include "FunctionManager.h"

namespace AST
{
    String::String(std::shared_ptr<Token>(token), Position pos) :
        Base(Type::String, pos),
        m_token(token),
        m_string(token->value())
    {}

    Data String::execute(std::shared_ptr<FunctionManager> fnManager, std::shared_ptr<VariableManager> varManager, Data d)
    {
        Data val;
        val.type = DataType::String;
        val.t_string = m_string;
        return val;
    }

}
