#ifndef UNARYOPERATION_H
#define UNARYOPERATION_H

#include "AST/Base.h"

namespace AST
{
    class UnaryOperation : public Base
    {
    private:
        std::shared_ptr<Token> m_token;
        std::shared_ptr<Base> m_expression;
    public:
        UnaryOperation(std::shared_ptr<Token> token, std::shared_ptr<Base> expression, Position pos);


        virtual Data execute(std::shared_ptr<FunctionManager> funManager, std::shared_ptr<VariableManager> varManager, Data d = Data());
    };
}

#endif //UNARYOPERATION_H
