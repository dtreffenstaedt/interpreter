#ifndef VARIABLEMANAGER_H
#define VARIABLEMANAGER_H

#include <string>
#include <map>
#include <memory>
#include <iostream>


#include "Exceptions.h"

namespace AST
{
    struct Data;
}

enum class DataType
{
    Quantity,
    Real,
    Integer,
    Boolean,
    String,
    List,
    Character,
    Void
};

static const std::wstring DataTypeStr[] =
{
    L"quantity",
    L"real",
    L"int",
    L"bool",
    L"String",
    L"List",
    L"char",
    L"void"
};

class VariableManager
{
public:
    struct Variable
    {
        DataType type;

        std::wstring name;

//        Quantity t_quantity;
        double t_real;
        int64_t t_int;
        std::wstring t_string;
        wchar_t t_char;
        bool t_bool;
//        std::list<Variable> t_list;
    };

private:
    class Scope
    {
    public:
        std::map<std::wstring, std::shared_ptr<Variable> > m_variables;
        std::shared_ptr<Scope> m_parent;

        explicit Scope(std::shared_ptr<Scope> p) :
            m_parent(p)
        {}

        explicit Scope() :
            m_parent(nullptr)
        {}

        bool insert(std::shared_ptr<Variable> v)
        {
            if (defined(v->name))
            {
                return false;
            }
            m_variables[v->name]=  v;
            return true;
        }

        bool defined(std::wstring name)
        {
            if ((m_variables.find(name) != m_variables.end()))
            {
                return true;
            }
            if (m_parent)
            {
                return (m_parent->defined(name));
            }
            return false;
        }

        std::shared_ptr<Variable> variable(std::wstring name)
        {
            if (m_variables.find(name) == m_variables.end())
            {
                if (m_parent)
                {
                    return m_parent->variable(name);
                }
                throw VariableUndefined(name);
            }
            return m_variables[name];
        }
    };

    std::shared_ptr<Scope> m_scope;

public:
    void create(std::wstring name, DataType t);
    void assign(std::wstring name, AST::Data value);
    AST::Data value(std::wstring name) const;

    bool defined(std::wstring name) const;

    DataType type(std::wstring name) const;

    void enterScope();

    void leaveScope();
};

#endif // VARIABLEMANAGER_H
