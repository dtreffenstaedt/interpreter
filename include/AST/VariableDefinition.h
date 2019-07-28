#ifndef VARIABLEDEFINITION_H
#define VARIABLEDEFINITION_H

#include "AST/Base.h"

namespace AST
{
    class VariableDefinition : public Base
    {
    private:
        std::shared_ptr<Token> m_type;
        std::shared_ptr<Base> m_variable;
        std::shared_ptr<Base> m_initialiser;
    public:
        VariableDefinition(std::shared_ptr<Token> type, std::shared_ptr<Base> variable, std::shared_ptr<Base> initialiser, Position pos);

        void setInitialiser(std::shared_ptr<Base> initialiser);
        
        std::wstring name() const;

        std::shared_ptr<Token> type();

        virtual Data execute(std::shared_ptr<FunctionManager> funManager, std::shared_ptr<VariableManager> varManager, Data d = Data());
    };

}

#endif // VARIABLEDEFINITION_H
