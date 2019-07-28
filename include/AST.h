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
            Default
        } action = Action::Default;

    //        Quantity t_quantity;
        double t_number = 0;
        std::wstring t_string;
    //        char t_char;
    //        bool t_bool;
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
            Compound,
            VariableDefinition,
            FunctionDefinition,
            FunctionCall,
            Assignment,
            Variable,
            Number
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

    class BinaryOperation : public Base
    {
    private:
        std::shared_ptr<Base> m_left;
        std::shared_ptr<Token> m_token;
        std::shared_ptr<Base> m_right;
    public:
        BinaryOperation(std::shared_ptr<Base> left, std::shared_ptr<Token> token, std::shared_ptr<Base> right, Position pos);


        virtual Data execute(std::shared_ptr<FunctionManager> funManager, std::shared_ptr<VariableManager> varManager, Data d = Data());
    };

    class UnaryOperation : public Base
    {
    private:
        std::shared_ptr<Token> m_token;
        std::shared_ptr<Base> m_expression;
    public:
        UnaryOperation(std::shared_ptr<Token> token, std::shared_ptr<Base> expression, Position pos);


        virtual Data execute(std::shared_ptr<FunctionManager> funManager, std::shared_ptr<VariableManager> varManager, Data d = Data());
    };

    class ReturnStatement : public Base
    {
    private:
        std::shared_ptr<Base> m_expression;
    public:
        ReturnStatement(std::shared_ptr<Base> expression, Position pos);


        virtual Data execute(std::shared_ptr<FunctionManager> funManager, std::shared_ptr<VariableManager> varManager, Data d = Data());
    };

    class Compound : public Base
    {
    private:
        std::list<std::shared_ptr<Base> > m_statements;
    public:
        Compound(Position pos);

        void append(std::shared_ptr<Base> statement);


        virtual Data execute(std::shared_ptr<FunctionManager> funManager, std::shared_ptr<VariableManager> varManager, Data d = Data());
    };

    class Variable : public Base
    {
    private:
        std::shared_ptr<Token> m_token;
        std::wstring m_name;

    public:
        Variable(std::shared_ptr<Token> token, Position pos);

        std::wstring name() const;

        virtual Data execute(std::shared_ptr<FunctionManager> funManager, std::shared_ptr<VariableManager> varManager, Data d = Data());
    };


    class VariableDefinition : public Base
    {
    private:
        std::shared_ptr<Token> m_type;
        std::shared_ptr<Base> m_variable;
        std::shared_ptr<Base> m_initialiser;
    public:
        VariableDefinition(std::shared_ptr<Token> type, std::shared_ptr<Base> variable, std::shared_ptr<Base> initialiser, Position pos);

        void setInitialiser(std::shared_ptr<Base> initialiser);
        
        std::wstring name() const;

        std::shared_ptr<Token> type();

        virtual Data execute(std::shared_ptr<FunctionManager> funManager, std::shared_ptr<VariableManager> varManager, Data d = Data());
    };


    class FunctionCall : public Base
    {
    private:
        std::shared_ptr<Token> m_token;
        std::list<std::shared_ptr<Base> > m_parameters;

    public:
        FunctionCall(std::shared_ptr<Token> token, Position pos);

        void addParam(std::shared_ptr<Base> parameter);

        virtual Data execute(std::shared_ptr<FunctionManager> funManager, std::shared_ptr<VariableManager> varManager, Data d = Data());
    };

    class FunctionDefinition : public Base
    {
    private:
        std::shared_ptr<Token> m_type;
        std::shared_ptr<Token> m_identifier;
        std::list<std::shared_ptr<VariableDefinition> > m_parameters;
        std::shared_ptr<Compound>  m_implementation;

    public:
        FunctionDefinition(std::shared_ptr<Token> type, std::shared_ptr<Token> identifier, Position pos);
        
        void addParam(std::shared_ptr<VariableDefinition> parameter);

        void setImplementation(std::shared_ptr<Compound> impl);
        
        std::wstring signature();

        virtual Data execute(std::shared_ptr<FunctionManager> funManager, std::shared_ptr<VariableManager> varManager, Data d = Data());
    };

    class Assignment : public Base
    {
    private:
        std::shared_ptr<Base> m_left;
        std::shared_ptr<Token> m_token;
        std::shared_ptr<Base> m_right;
    public:
        Assignment(std::shared_ptr<Base> left, std::shared_ptr<Token> token, std::shared_ptr<Base> right, Position pos);

        virtual Data execute(std::shared_ptr<FunctionManager> funManager, std::shared_ptr<VariableManager> varManager, Data d = Data());
    };


    class Number : public Base
    {
    private:
        std::shared_ptr<Token> m_token;
        double m_number;
    public:
        Number(std::shared_ptr<Token>(token), Position pos);

        virtual Data execute(std::shared_ptr<FunctionManager> funManager, std::shared_ptr<VariableManager> varManager, Data d = Data());
    };
}
#endif // AST_H
