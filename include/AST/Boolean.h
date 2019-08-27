#ifndef BOOLEAN_H
#define BOOLEAN_H

#include "AST/Base.h"

namespace AST
{
    class Boolean : public Base
    {
    private:
        std::shared_ptr<Token> m_token;
        bool m_bool;
    public:
        Boolean(std::shared_ptr<Token>(token), Position pos);

        virtual Data execute(std::shared_ptr<FunctionManager> funManager, std::shared_ptr<VariableManager> varManager, Data d = Data());
    };
}

#endif // BOOLEAN_H
