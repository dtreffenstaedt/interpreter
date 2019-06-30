#include "VariableManager.h"

#include <iostream>

bool VariableManager::create(std::wstring name, Variable::Type t)
{
    if (!m_scope)
    {
        return false;
    }
    if (defined(name))
    {
        throw VariableExists(name);
    }
    std::shared_ptr<Variable> v = std::make_shared<Variable>(Variable());

    v->name = name;
    v->type = t;
    v->t_number = 0;
    std::wcout<<"created Variable "<<name<<"\n";
    return m_scope->insert(v);
}

bool VariableManager::assign(std::wstring name, double value)
{
    if (!m_scope)
    {
        return false;
    }
    std::shared_ptr<Variable> var = m_scope->variable(name);
    if (!var)
    {
        throw VariableUndefined(name);
    }

    var->t_number = value;

    std::wcout<<"assigned value"<<std::to_wstring(value)<<" to Variable "<<name<<"\n";
    return true;
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

void VariableManager::enterScope()
{
    std::wcout<<"entering scope\n";
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
    std::wcout<<"leaving scope\n";
    if (m_scope)
    {
        std::shared_ptr<Scope> s = m_scope;
        m_scope = s->m_parent;
    }
}
