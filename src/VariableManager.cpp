#include "VariableManager.hpp"

bool VariableManager::create(std::string name, int value)
{
    if (!m_scope)
    {
        return false;
    }
    Variable *v = new Variable();

    v->name = name;
    v->type = Variable::Type::Integer;
    v->t_int = value;

    return m_scope->insert(v);
}

bool VariableManager::create(std::string name, bool value)
{
    if (!m_scope)
    {
        return false;
    }
    Variable *v = new Variable();

    v->name = name;
    v->type = Variable::Type::Boolean;
    v->t_bool = value;

    return m_scope->insert(v);
}

bool VariableManager::create(std::string name, std::string value)
{
    if (!m_scope)
    {
        return false;
    }
    Variable *v = new Variable();

    v->name = name;
    v->type = Variable::Type::String;
    v->t_str = value;

    return m_scope->insert(v);
}

bool VariableManager::create(std::string name, float value)
{
    if (!m_scope)
    {
        return false;
    }
    Variable *v = new Variable();

    v->name = name;
    v->type = Variable::Type::Float;
    v->t_float = value;

    return m_scope->insert(v);
}

bool VariableManager::defined(std::string name) const
{
    if (!m_scope)
    {
        return false;
    }
    return m_scope->defined(name);
}

VariableManager::Variable::Type VariableManager::type(std::string name) const
{
    Variable *var = m_scope->variable(name);
    return var->type;
}

bool VariableManager::value(std::string name, int &value) const
{
    if (!m_scope)
    {
        return false;
    }
    Variable *var = m_scope->variable(name);
    if (!var)
    {
        return false;
    }
    if (var->type != Variable::Type::Integer)
    {
        return false;
    }

    value = var->t_int;
    return true;
}

bool VariableManager::value(std::string name, float &value) const
{
    if (!m_scope)
    {
        return false;
    }
    Variable *var = m_scope->variable(name);
    if (!var)
    {
        return false;
    }
    if (var->type != Variable::Type::Float)
    {
        return false;
    }

    value = var->t_float;
    return true;
}

bool VariableManager::value(std::string name, bool &value) const
{
    if (!m_scope)
    {
        return false;
    }
    Variable *var = m_scope->variable(name);
    if (!var)
    {
        return false;
    }
    if (var->type != Variable::Type::Boolean)
    {
        return false;
    }

    value = var->t_bool;
    return true;
}

bool VariableManager::value(std::string name, std::string &value) const
{
    if (!m_scope)
    {
        return false;
    }
    Variable *var = m_scope->variable(name);
    if (!var)
    {
        return false;
    }
    if (var->type != Variable::Type::String)
    {
        return false;
    }

    value = var->t_str;
    return true;
}

void VariableManager::newScope()
{
    if (!m_scope)
    {
        m_scope = new Scope();
    }
    else
    {
        Scope *s = m_scope;
        m_scope = new Scope(s);
    }
}

void VariableManager::leaveScope()
{
    if (m_scope)
    {
        Scope *s = m_scope;
        m_scope = s->m_parent;
        delete s;
    }
}