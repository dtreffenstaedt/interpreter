#include "AST/FunctionDefinition.h"

#include <iostream>
#include <cmath>

#include "FunctionManager.h"

namespace AST
{
    FunctionDefinition::FunctionDefinition(std::shared_ptr<Token> type, std::shared_ptr<Token> identifier, Position pos) :
    Base(Type::FunctionDefinition, pos),
    m_type(type),
    m_identifier(identifier)
    {}
    
    void FunctionDefinition::addParam(std::shared_ptr<VariableDefinition> parameter)
    {
        m_parameters.push_back(parameter);
    }

    void FunctionDefinition::setImplementation(std::shared_ptr<Compound> impl)
    {
        m_implementation = impl;
    }
    
    std::wstring FunctionDefinition::signature()
    {
        std::wstring sig = m_identifier->value();
        sig += L":";
        for (auto i = m_parameters.begin(); i != m_parameters.end(); i++)
        {
            std::shared_ptr<VariableDefinition> v = std::static_pointer_cast<VariableDefinition>(*i);
            sig += L" ";
//            sig += v->type()->value();
            sig += DataTypeStr[((int) v->type()->type())-5];
        }
        return sig;
    }

    Data FunctionDefinition::execute(std::shared_ptr<FunctionManager> fnManager, std::shared_ptr<VariableManager> varManager, Data d)
    {
        fnManager->create(signature(), m_implementation, m_parameters, (DataType) (((int) m_type->type())-5));
        return Data();
    }

}
