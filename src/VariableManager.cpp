#include "VariableManager.h"

#include <iostream>

#include "AST.h"

void VariableManager::create(std::wstring name, DataType t)
{
    if (!m_scope)
    {
        throw NoScope();
    }
    if (defined(name))
    {
        throw VariableExists(name);
    }
    std::shared_ptr<Variable> v = std::make_shared<Variable>(Variable());

    v->name = name;
    v->type = t;
    v->t_real = 0.0;
    v->t_int = 0;
    v->t_char = 0;
    v->t_bool = false;
    v->t_string = L"";
//    std::wcout<<L"created Variable "<<name<<L"("<<DataTypeStr[(int) v->type]<<L")\n";
    m_scope->insert(v);
}
void VariableManager::assign(std::wstring name, AST::Data value)
{
    if (!m_scope)
    {
        throw NoScope();
    }
    std::shared_ptr<Variable> var = m_scope->variable(name);
    if (!var)
    {
        throw VariableUndefined(name);
    }
    if (var->type != value.type)
    {
        throw WrongType();
    }
    
    if (var->type == DataType::Real)
    {
          var->t_real = value.t_real;
//        std::wcout<<"assigned value "<<std::to_wstring(value.t_number)<<" to Variable "<<name<<"\n";
    }
    else if (var->type == DataType::Integer)
    {
          var->t_int = value.t_int;
//        std::wcout<<"assigned value "<<std::to_wstring(value.t_number)<<" to Variable "<<name<<"\n";
    }
    else if (var->type == DataType::String)
    {
        var->t_string = value.t_string;
//        std::wcout<<"assigned value '"<<var->t_string<<"' to Variable "<<name<<"\n";
    }
    else if (var->type == DataType::Boolean)
    {
        var->t_bool = value.t_bool;
//        std::wcout<<"assigned value '"<<var->t_bool<<"' to Variable "<<name<<"\n";
    }
    else if (var->type == DataType::Character)
    {
        var->t_char = value.t_char;
//        std::wcout<<"assigned value '"<<var->t_char<<"' to Variable "<<name<<"\n";
    }
}

bool VariableManager::defined(std::wstring name) const
{
    if (!m_scope)
    {
        throw NoScope();
    }
    return m_scope->defined(name);
}

DataType VariableManager::type(std::wstring name) const
{
    return (m_scope->variable(name))->type;
}

AST::Data VariableManager::value(std::wstring name) const
{
    if (!m_scope)
    {
        throw NoScope();
        return AST::Data();
    }
    std::shared_ptr<Variable> var = m_scope->variable(name);
    if (!var)
    {
        return AST::Data();
    }
    AST::Data d;
    d.type = var->type;
    switch (d.type)
    {
        case DataType::Real:
            d.t_real = var->t_real;
            break;
        case DataType::Integer:
            d.t_int = var->t_int;
            break;
        case DataType::String:
            d.t_string = var->t_string;
            break;
        case DataType::Character:
            d.t_char = var->t_char;
            break;
        case DataType::Boolean:
            d.t_bool = var->t_bool;
            break;
        default:
            throw WrongType();
            break;
    }

    return d;
}

void VariableManager::enterScope()
{
//    std::wcout<<"entering scope\n";
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
//    std::wcout<<"leaving scope\n";
    if (m_scope)
    {
        std::shared_ptr<Scope> s = m_scope;
        m_scope = s->m_parent;
    }
}
