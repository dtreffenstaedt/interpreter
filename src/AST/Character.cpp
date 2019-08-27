#include "AST/Character.h"

#include <iostream>
#include <cmath>

#include "FunctionManager.h"

namespace AST
{
    Character::Character(std::shared_ptr<Token>(token), Position pos) :
        Base(Type::Character, pos),
        m_token(token),
        m_char(token->toCharacter())
    {}

    Data Character::execute(std::shared_ptr<FunctionManager> fnManager, std::shared_ptr<VariableManager> varManager, Data d)
    {
        Data val;
        val.type = DataType::Character;
        val.t_char = m_char;
        return val;
    }

}
