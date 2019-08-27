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
        if ((*m_type) == Token::Type::KeywordReal)
        {
            def.type = DataType::Real;
        }
        else if ((*m_type) == Token::Type::KeywordInteger)
        {
            def.type = DataType::Integer;
        }
        else if ((*m_type) == Token::Type::KeywordString)
        {
            def.type = DataType::String;
        }
        else if ((*m_type) == Token::Type::KeywordChar)
        {
            def.type = DataType::Character;
        }
        else if ((*m_type) == Token::Type::KeywordBool)
        {
            def.type = DataType::Boolean;
        }
        def.action = Data::Action::Definition;
        m_variable->execute(fnManager, varManager, def);
        if (m_initialiser->type != Type::Empty)
        {
            Data init = m_initialiser->execute(fnManager, varManager);
            init.action = Data::Action::Assign;
            m_variable->execute(fnManager, varManager, init);
        }
        return Data();
    }

}
