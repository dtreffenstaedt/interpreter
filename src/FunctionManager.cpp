#include "FunctionManager.h"
#include "VariableManager.h"
#include "AST.h"

#include <iostream>

void FunctionManager::create(std::wstring signature, std::shared_ptr<AST::Compound> implementation, std::list<std::shared_ptr<AST::VariableDefinition> > parameters, DataType t)
{
    if (!m_scope)
    {
        throw NoScope();
    }
    if (defined(signature))
    {
        throw FunctionExists(signature);
    }
    std::shared_ptr<Function> f = std::make_shared<Function>(Function());

    f->signature = signature;
    f->type = t;
    f->parameters = parameters;
    f->implementation = implementation;
//    std::wcout<<"created Function "<<signature<<"\n";
    m_scope->insert(f);
}

AST::Data FunctionManager::execute(std::wstring name, std::shared_ptr<VariableManager> varMgr, std::shared_ptr<FunctionManager> fnMgr, std::list<std::shared_ptr<AST::Base> > parameters)
{

    std::wstring sig = name;
    sig += L":";
    std::list<AST::Data> params;
    for (auto i = parameters.begin(); i != parameters.end(); i++)
    {
        AST::Data d = (*i)->execute(fnMgr, varMgr);
        sig += L" ";
        sig += DataTypeStr[(int) d.type];
        params.push_back(d);
    }

//    std::wcout<<"executing Function "<<sig<<"\n";
    if (!m_scope)
    {
        throw NoScope();
        return AST::Data();
    }
    std::shared_ptr<Function> f = m_scope->function(sig);
    if (!f)
    {
        throw FunctionUndefined(sig);
        return AST::Data();
    }

    std::shared_ptr<VariableManager> varManager = std::make_shared<VariableManager>(VariableManager());
    std::shared_ptr<FunctionManager> fnManager = shared_from_this();
    varManager->enterScope();
    fnManager->enterScope();

    auto p = f->parameters.begin();
    auto i = params.begin();

    while (p != f->parameters.end() && i != params.end())
    {
        (*p)->execute(fnManager, varManager);
        varManager->assign((*p)->name(), (*i));

        p++;
        i++;
    }

    AST::Data ret =  f->implementation->execute(fnManager, varManager);
    fnManager->leaveScope();
    return ret;
}

bool FunctionManager::defined(std::wstring signature) const
{
    if (!m_scope)
    {
        throw NoScope();
        return false;
    }
    return m_scope->defined(signature);
}

void FunctionManager::enterScope()
{
//    std::wcout<<"entering function scope\n";
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

void FunctionManager::leaveScope()
{
//    std::wcout<<"leaving function scope\n";
    if (m_scope)
    {
        std::shared_ptr<Scope> s = m_scope;
        m_scope = s->m_parent;
    }
}
