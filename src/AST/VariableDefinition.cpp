#include "AST/VariableDefinition.h"

#include <iostream>
#include <cmath>

#include "FunctionManager.h"

namespace AST
{
   VariableDefinition::VariableDefinition(std::shared_ptr<Token> type, std::shared_ptr<Base> variable, std::shared_ptr<Base> initialiser, Position pos) :
        Base(Type::VariableDefinition, pos),
        m_type(type),
        m_variable(variable),
        m_initialiser(initialiser)
    {}

    void VariableDefinition::setInitialiser(std::shared_ptr<Base> initialiser)
    {
        m_initialiser = initialiser;
    }

    std::shared_ptr<Token> VariableDefinition::type()
    {
        return m_type;
    }

    std::wstring VariableDefinition::name() const
    {
        return std::static_pointer_cast<Variable>(m_variable)->name();
    }

    Data VariableDefinition::execute(std::shared_ptr<FunctionManager> fnManager, std::shared_ptr<VariableManager> varManager, Data d)
    {
        Data def;
        def.action = Data::Action::Definition;
        m_variable->execute(fnManager, varManager, def);
        m_variable->execute(fnManager, varManager, m_initialiser->execute(fnManager, varManager));
        return Data();
    }

}
