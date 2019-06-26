#ifndef VARIABLEMANAGER_H
#define VARIABLEMANAGER_H

#include <string>
#include <map>

class VariableManager
{
public:
    struct Variable
    {
        enum class Type
        {
            Integer,
            String,
            Float,
            Boolean,
            Character
        } type;

        std::string name;

        int t_int;
        std::string t_str;
        char t_char;
        float t_float;
        bool t_bool;
    };

private:
    class Scope
    {
    public:
        std::map<std::string, Variable*> m_variables;
        Scope *m_parent;

        explicit Scope(Scope *p) :
            m_parent(p)
        {}

        explicit Scope() :
            m_parent(0)
        {}

        bool insert(Variable* v)
        {
            if (defined(v->name))
            {
                return false;
            }
            m_variables[v->name]=  v;
            return true;
        }

        bool defined(std::string name)
        {
            if (!m_parent)
            {
                return (m_variables.find(name) != m_variables.end());
            }
            return (m_variables.find(name) != m_variables.end()) || (m_parent->defined(name));
        }

        Variable* variable(std::string name)
        {
            if (m_variables.find(name) == m_variables.end())
            {
                return 0;
            }
            return m_variables[name];
        }

        ~Scope()
        {
            for (std::map<std::string, Variable*>::iterator i = m_variables.end(); i != m_variables.end(); ++i)
            {
                delete (i->second);
            }
        }
    } *m_scope;

public:
    bool create(std::string name, int value);
    bool create(std::string name, bool value);

    bool create(std::string name, std::string value);

    bool create(std::string name, float value);

    bool defined(std::string name) const;

    Variable::Type type(std::string name) const;
    bool value(std::string name, int &value) const;

    bool value(std::string name, float &value) const;
    bool value(std::string name, bool &value) const;

    bool value(std::string name, std::string &value) const;

    void newScope();

    void leaveScope();
};

#endif // VARIABLEMANAGER_H
