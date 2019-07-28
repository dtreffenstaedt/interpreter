#include "AST/FunctionCall.h"

#include <iostream>
#include <cmath>

#include "FunctionManager.h"

namespace AST
{
   FunctionCall::FunctionCall(std::shared_ptr<Token> token, Position pos) :
        Base(Type::FunctionCall, pos),
        m_token(token)
    {}

    void FunctionCall::addParam(std::shared_ptr<Base> parameter)
    {
        m_parameters.push_back(parameter);
    }

    Data FunctionCall::execute(std::shared_ptr<FunctionManager> fnManager, std::shared_ptr<VariableManager> varManager, Data d)
    {
        return fnManager->execute(m_token->value(), varManager, fnManager, m_parameters);
    }
}
