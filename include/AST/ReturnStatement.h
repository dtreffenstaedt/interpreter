#ifndef RETURNSTATEMENT_H
#define RETURNSTATEMENT_H

#include "AST/Base.h"

namespace AST
{
    class ReturnStatement : public Base
    {
    private:
        std::shared_ptr<Base> m_expression;
    public:
        ReturnStatement(std::shared_ptr<Base> expression, Position pos);


        virtual Data execute(std::shared_ptr<FunctionManager> funManager, std::shared_ptr<VariableManager> varManager, Data d = Data());
    };
}

#endif // RETURNSTATEMENT_H
