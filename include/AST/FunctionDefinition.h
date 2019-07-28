#ifndef FUNCTIONDEFINITION_H
#define FUNCTIONDEFINITION_H

#include "AST/Base.h"

#include "AST/VariableDefinition.h"
#include "AST/Compound.h"

namespace AST
{
    class FunctionDefinition : public Base
    {
    private:
        std::shared_ptr<Token> m_type;
        std::shared_ptr<Token> m_identifier;
        std::list<std::shared_ptr<VariableDefinition> > m_parameters;
        std::shared_ptr<Compound>  m_implementation;

    public:
        FunctionDefinition(std::shared_ptr<Token> type, std::shared_ptr<Token> identifier, Position pos);
        
        void addParam(std::shared_ptr<VariableDefinition> parameter);

        void setImplementation(std::shared_ptr<Compound> impl);
        
        std::wstring signature();

        virtual Data execute(std::shared_ptr<FunctionManager> funManager, std::shared_ptr<VariableManager> varManager, Data d = Data());
    };
}

#endif // FUNCTIONDEFINITION_H
