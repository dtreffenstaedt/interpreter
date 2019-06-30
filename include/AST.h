#ifndef AST_H
#define AST_H

#include <memory>
#include <list>

#include "Token.h"
#include "VariableManager.h"

struct Data
{
    enum class Type
    {
//            Quantity,
        Number,
//            Boolean,
        String,
//            Character,
//            List
        Void,
        Definition
    } type = Type::Void;

//        Quantity t_quantity;
    double t_number = 0;
    std::wstring t_string;
//        char t_char;
//        bool t_bool;
//        std::list<Variable> t_list;
};

namespace AST
{
    class Base
    {
    public:
        enum class Type
        {
            Empty,
            BinaryOperation,
            UnaryOperation,
            Compound,
            Definition,
            Assignment,
            Variable,
            Number
        } type = Type::Empty;

        Position position;

        virtual void print() = 0;
        virtual Data execute(std::shared_ptr<VariableManager>, Data d = Data()) = 0;
        explicit Base(Type t = Type::Empty, Position pos = {1,1}) :
            type(t)
        {}
    };

    class Empty : public Base
    {
    public:
        explicit Empty(Position pos);

        virtual void print();

        virtual Data execute(std::shared_ptr<VariableManager> varManager, Data d);
    };

    class BinaryOperation : public Base
    {
    private:
        std::shared_ptr<Base> m_left;
        std::shared_ptr<Token> m_token;
        std::shared_ptr<Base> m_right;
    public:
        BinaryOperation(std::shared_ptr<Base> left, std::shared_ptr<Token> token, std::shared_ptr<Base> right, Position pos);

        virtual void print();

        virtual Data execute(std::shared_ptr<VariableManager> varManager, Data d);
    };

    class UnaryOperation : public Base
    {
    private:
        std::shared_ptr<Token> m_token;
        std::shared_ptr<Base> m_expression;
    public:
        UnaryOperation(std::shared_ptr<Token> token, std::shared_ptr<Base> expression, Position pos);

        virtual void print();

        virtual Data execute(std::shared_ptr<VariableManager> varManager, Data d);
    };

    class Compound : public Base
    {
    private:
        std::list<std::shared_ptr<Base> > m_statements;
    public:
        Compound(Position pos);

        void append(std::shared_ptr<Base> statement);

        virtual void print();

        virtual Data execute(std::shared_ptr<VariableManager> varManager, Data d);
    };

    class Definition : public Base
    {
    private:
        std::shared_ptr<Token> m_type;
        std::shared_ptr<Base> m_variable;
        std::shared_ptr<Base> m_initialiser;
    public:
        Definition(std::shared_ptr<Token> type, std::shared_ptr<Base> variable, std::shared_ptr<Base> initialiser, Position pos);

        virtual void print();

        virtual Data execute(std::shared_ptr<VariableManager> varManager, Data d);
    };

    class Assignment : public Base
    {
    private:
        std::shared_ptr<Base> m_left;
        std::shared_ptr<Token> m_token;
        std::shared_ptr<Base> m_right;
    public:
        Assignment(std::shared_ptr<Base> left, std::shared_ptr<Token> token, std::shared_ptr<Base> right, Position pos);

        virtual void print();

        virtual Data execute(std::shared_ptr<VariableManager> varManager, Data d);
    };

    class Variable : public Base
    {
    private:
        std::shared_ptr<Token> m_token;
        std::wstring m_name;
    public:
        Variable(std::shared_ptr<Token>(token), Position pos);

        virtual void print();

        virtual Data execute(std::shared_ptr<VariableManager> varManager, Data d);
    };

    class Number : public Base
    {
    private:
        std::shared_ptr<Token> m_token;
        double m_number;
    public:
        Number(std::shared_ptr<Token>(token), Position pos);

        virtual  void print();

        virtual Data execute(std::shared_ptr<VariableManager> varManager, Data d);
    };
}
#endif // AST_H
