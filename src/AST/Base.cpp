#include "AST/Base.h"

#include <iostream>
#include <cmath>

#include "FunctionManager.h"

namespace AST
{
    Empty::Empty(Position pos) :
        Base(Type::Empty, pos)
    {}

    Data Empty::execute(std::shared_ptr<FunctionManager> fnManager, std::shared_ptr<VariableManager> varManager, Data d)
    {
        return Data();
    }
}
