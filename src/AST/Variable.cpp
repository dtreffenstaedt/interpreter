#include "AST/Variable.h"

#include <iostream>
#include <cmath>

#include "FunctionManager.h"

namespace AST
{
    Variable::Variable(std::shared_ptr<Token>(token), Position pos) :
        Base(Type::Variable, pos),
        m_token(token),
        m_name(token->value())
    {}

    std::wstring Variable::name() const
    {
        return m_name;
    }

    Data Variable::execute(std::shared_ptr<FunctionManager> fnManager, std::shared_ptr<VariableManager> varManager, Data d)
    {
        if (d.action == Data::Action::Assign)
        {
            varManager->assign(m_name, d);
            return Data();
        }
        else if (d.action == Data::Action::Definition)
        {
            varManager->create(m_name, d.type);
            return Data();
        }
        return varManager->value(m_name);
    }

}
