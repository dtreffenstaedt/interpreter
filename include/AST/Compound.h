#ifndef COMPOUND_H
#define COMPOUND_H

#include "AST/Base.h"

namespace AST
{
    class Compound : public Base
    {
    private:
        std::list<std::shared_ptr<Base> > m_statements;
    public:
        Compound(Position pos);

        void append(std::shared_ptr<Base> statement);


        virtual Data execute(std::shared_ptr<FunctionManager> funManager, std::shared_ptr<VariableManager> varManager, Data d = Data());
    };
}

#endif // COMPOUND_H
