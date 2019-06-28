#include "VariableManager.h"

bool VariableManager::create(std::wstring name, double value)
{
    if (!m_scope)
    {
        return false;
    }
    std::shared_ptr<Variable> v = std::make_shared<Variable>(Variable());

    v->name = name;
    v->type = Variable::Type::Number;
    v->t_number = value;

    return m_scope->insert(v);
}

bool VariableManager::defined(std::wstring name) const
{
    if (!m_scope)
    {
        return false;
    }
    return m_scope->defined(name);
}

VariableManager::Variable::Type VariableManager::type(std::wstring name) const
{
    return (m_scope->variable(name))->type;
}

bool VariableManager::value(std::wstring name, double& value)
{
    if (!m_scope)
    {
        return false;
    }
    std::shared_ptr<Variable> var = m_scope->variable(name);
    if (!var)
    {
        return false;
    }
    if (var->type != Variable::Type::Number)
    {
        return false;
    }

    value = var->t_number;
    return true;
}

void VariableManager::newScope()
{
    if (!m_scope)
    {
        m_scope = std::make_shared<Scope>(Scope());
    }
    else
    {
        std::shared_ptr<Scope> s = m_scope;
        m_scope = std::make_shared<Scope>(Scope(s));
    }
}

void VariableManager::leaveScope()
{
    if (m_scope)
    {
        std::shared_ptr<Scope> s = m_scope;
        m_scope = s->m_parent;
    }
}
