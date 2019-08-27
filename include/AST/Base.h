#ifndef AST_H
#define AST_H

#include <memory>
#include <list>

#include "Token.h"
#include "VariableManager.h"

class FunctionManager;

namespace AST
{
    struct Data
    {
        DataType type = DataType::Void;

        enum class Action
        {
            Definition,
            Call,
            Assign,
            Default
        } action = Action::Default;

    //        Quantity t_quantity;
        double t_real = 0;
        double t_int = 0;
        std::wstring t_string;
        wchar_t t_char;
        bool t_bool;
    //        std::list<Variable> t_list;
    };

    class Base
    {
    public:
        enum class Type
        {
            Empty,
            BinaryOperation,
            UnaryOperation,
            ReturnStatement,
            PrintStatement,
            Compound,
            VariableDefinition,
            FunctionDefinition,
            FunctionCall,
            Assignment,
            Variable,
            Real,
            Integer,
            String,
            Character,
            Boolean
        } type = Type::Empty;

        Position position;

        virtual Data execute(std::shared_ptr<FunctionManager> funManager, std::shared_ptr<VariableManager> varManager, Data d = Data()) = 0;

        explicit Base(Type t = Type::Empty, Position pos = {1,1}) :
            type(t)
        {}
    };

    class Empty : public Base
    {
    public:
        explicit Empty(Position pos);


        virtual Data execute(std::shared_ptr<FunctionManager> funManager, std::shared_ptr<VariableManager> varManager, Data d = Data());
    };
}
#endif // AST_H
