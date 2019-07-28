#ifndef FUNCTIONCALL_H
#define FUNCTIONCALL_H

#include "AST/Base.h"

namespace AST
{
    class FunctionCall : public Base
    {
    private:
        std::shared_ptr<Token> m_token;
        std::list<std::shared_ptr<Base> > m_parameters;

    public:
        FunctionCall(std::shared_ptr<Token> token, Position pos);

        void addParam(std::shared_ptr<Base> parameter);

        virtual Data execute(std::shared_ptr<FunctionManager> funManager, std::shared_ptr<VariableManager> varManager, Data d = Data());
    };


}

#endif // FUNCTIONCALL_H
