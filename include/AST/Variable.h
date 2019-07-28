#ifndef VARIABLE_H
#define VARIABLE_H

#include "AST/Base.h"

namespace AST
{
    class Variable : public Base
    {
    private:
        std::shared_ptr<Token> m_token;
        std::wstring m_name;

    public:
        Variable(std::shared_ptr<Token> token, Position pos);

        std::wstring name() const;

        virtual Data execute(std::shared_ptr<FunctionManager> funManager, std::shared_ptr<VariableManager> varManager, Data d = Data());
    };
}

#endif // VARIABLE_H
