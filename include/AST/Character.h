#ifndef CHARACTER_H
#define CHARACTER_H

#include "AST/Base.h"

namespace AST
{
    class Character : public Base
    {
    private:
        std::shared_ptr<Token> m_token;
        char m_char;
    public:
        Character(std::shared_ptr<Token>(token), Position pos);

        virtual Data execute(std::shared_ptr<FunctionManager> funManager, std::shared_ptr<VariableManager> varManager, Data d = Data());
    };
}

#endif // CHARACTER_H
