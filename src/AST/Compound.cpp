#include "AST/Compound.h"

#include <iostream>
#include <cmath>

#include "FunctionManager.h"

namespace AST
{
    Compound::Compound(Position pos) :
        Base(Type::Compound, pos)
    {}

    void Compound::append(std::shared_ptr<Base> statement)
    {
        m_statements.push_back(statement);
    }

    Data Compound::execute(std::shared_ptr<FunctionManager> fnManager, std::shared_ptr<VariableManager> varManager, Data d)
    {
        varManager->enterScope();
        fnManager->enterScope();
        Data ret;
        for (auto i = m_statements.begin(); i != m_statements.end(); ++i)
        {
            if ((*i)->type == Base::Type::ReturnStatement)
            {
                ret = (*i)->execute(fnManager, varManager);
                std::wcout<<"Returning\n";
                break;
            }
            else
            {
                (*i)->execute(fnManager, varManager);
            }
        }
        varManager->leaveScope();
        fnManager->leaveScope();
        return ret;
    }

}
