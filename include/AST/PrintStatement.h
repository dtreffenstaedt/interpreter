#ifndef PRINTSTATEMENT_H
#define PRINTSTATEMENT_H

#include "AST/Base.h"

namespace AST
{
    class PrintStatement : public Base
    {
    private:
        std::shared_ptr<Base> m_expression;
    public:
        PrintStatement(std::shared_ptr<Base> expression, Position pos);


        virtual Data execute(std::shared_ptr<FunctionManager> funManager, std::shared_ptr<VariableManager> varManager, Data d = Data());
    };
}

#endif // PRINTSTATEMENT_H
