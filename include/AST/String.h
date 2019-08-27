#ifndef STRING_H
#define STRING_H

#include "AST/Base.h"

namespace AST
{
    class String : public Base
    {
    private:
        std::shared_ptr<Token> m_token;
        std::wstring m_string;
    public:
        String(std::shared_ptr<Token>(token), Position pos);

        virtual Data execute(std::shared_ptr<FunctionManager> funManager, std::shared_ptr<VariableManager> varManager, Data d = Data());
    };
}

#endif // STRING_H
