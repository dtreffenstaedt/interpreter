#ifndef INTEGER_H
#define INTEGER_H

#include "AST/Base.h"

namespace AST
{
    class Integer : public Base
    {
    private:
        std::shared_ptr<Token> m_token;
        int64_t m_number;
    public:
        Integer(std::shared_ptr<Token>(token), Position pos);

        virtual Data execute(std::shared_ptr<FunctionManager> funManager, std::shared_ptr<VariableManager> varManager, Data d = Data());
    };
}

#endif // INTEGER_H
