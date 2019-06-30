#ifndef VARIABLEMANAGER_H
#define VARIABLEMANAGER_H

#include <string>
#include <map>
#include <memory>
#include <iostream>


#include "Exceptions.h"

class VariableManager
{
public:
    struct Variable
    {
        enum class Type
        {
//            Quantity,
            Number,
//            Boolean,
//            String,
//            Character,
//            List
        } type;

        std::wstring name;

//        Quantity t_quantity;
        double t_number;
//        std::wstring t_string;
//        char t_char;
//        bool t_bool;
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
    bool create(std::wstring name, Variable::Type t = Variable::Type::Number);
    bool assign(std::wstring name, const double value);
    bool value(std::wstring name, double& value);
/*    bool create(std::wstring name, Number value);
    bool create(std::wstring name, Quantity value);
    bool create(std::wstring name, bool value);
    bool create(std::wstring name, wchar_t value);
    bool create(std::wstring name, std::list<Variable> value);
    bool create(std::wstring name, std::wstring value);

    bool assign(std::wstring name, Number value);
    bool assign(std::wstring name, Quantity value);
    bool assign(std::wstring name, bool value);
    bool assign(std::wstring name, wchar_t value);
    bool assing(std::wstring name, std::list<Variable> value);
    bool assing(std::wstring name, std::wstring value);

    bool value(std::wstring name, Number& value);
    bool value(std::wstring name, Quantity& value);
    bool value(std::wstring name, bool& value);
    bool value(std::wstring name, wchar_t& value);
    bool value(std::wstring name, std::list<Variable>& value);
    bool value(std::wstring name, std::wstring& value);
*/
    bool defined(std::wstring name) const;

    Variable::Type type(std::wstring name) const;

    void enterScope();

    void leaveScope();
};

#endif // VARIABLEMANAGER_H
