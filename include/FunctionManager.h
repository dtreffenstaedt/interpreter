#ifndef FUNCTIONMANAGER_H
#define FUNCTIONMANAGER_H

#include <string>
#include <map>
#include <list>
#include <memory>
#include <iostream>


#include "Exceptions.h"
#include "VariableManager.h"

#include "AST.h"

class FunctionManager : public std::enable_shared_from_this<FunctionManager>
{
public:
    struct Function
    {
        DataType type = DataType::Void;

        std::wstring signature;

        std::list<std::shared_ptr<AST::VariableDefinition> > parameters;

        std::shared_ptr<AST::Compound> implementation;
    };

private:
    class Scope
    {
    public:
        std::map<std::wstring, std::shared_ptr<Function> > m_functions;
        std::shared_ptr<Scope> m_parent;

        explicit Scope(std::shared_ptr<Scope> p) :
            m_parent(p)
        {}

        explicit Scope() :
            m_parent(nullptr)
        {}

        bool insert(std::shared_ptr<Function> f)
        {
            if (defined(f->signature))
            {
                return false;
            }
            m_functions[f->signature] =  f;
            return true;
        }

        bool defined(std::wstring signature)
        {
            if ((m_functions.find(signature) != m_functions.end()))
            {
                return true;
            }
            if (m_parent)
            {
                return (m_parent->defined(signature));
            }
            return false;
        }

        std::shared_ptr<Function> function(std::wstring signature)
        {
            if (m_functions.find(signature) == m_functions.end())
            {
                if (m_parent)
                {
                    return m_parent->function(signature);
                }
                throw FunctionUndefined(signature);
            }
            return m_functions[signature];
        }
    };

    std::shared_ptr<Scope> m_scope;

public:

    void create(std::wstring signature, std::shared_ptr<AST::Compound>  implementation, std::list<std::shared_ptr<AST::VariableDefinition> > parameters, DataType t);

    AST::Data execute(std::wstring name, std::shared_ptr<VariableManager> varMgr, std::shared_ptr<FunctionManager> fnMgr, std::list<std::shared_ptr<AST::Base> > parameters);

    bool defined(std::wstring signature) const;

    void enterScope();

    void leaveScope();
};

#endif // FUNCTIONMANAGER_H
