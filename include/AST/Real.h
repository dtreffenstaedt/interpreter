#ifndef REAL_H
#define REAL_H

#include "AST/Base.h"

namespace AST
{
    class Real : public Base
    {
    private:
        std::shared_ptr<Token> m_token;
        double m_number;
    public:
        Real(std::shared_ptr<Token>(token), Position pos);

        virtual Data execute(std::shared_ptr<FunctionManager> funManager, std::shared_ptr<VariableManager> varManager, Data d = Data());
    };
}

#endif // REAL_H
