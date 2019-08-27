#include "AST/PrintStatement.h"

#include <iostream>
#include <cmath>

#include "FunctionManager.h"

namespace AST
{
    PrintStatement::PrintStatement(std::shared_ptr<Base> expression, Position pos) :
        Base(Type::PrintStatement, pos),
        m_expression(expression)
    {}

    Data PrintStatement::execute(std::shared_ptr<FunctionManager> fnManager, std::shared_ptr<VariableManager> varManager, Data d)
    {
        Data exp = m_expression->execute(fnManager, varManager);
        
        switch (exp.type)
        {
        case DataType::Real:
            std::wcout<<std::to_wstring(exp.t_real);
            break;
        case DataType::Integer:
            std::wcout<<std::to_wstring(exp.t_int);
            break;
        case DataType::String:
            std::wcout<<exp.t_string;
            break;
        case DataType::Character:
            std::wcout<<exp.t_char;
            break;
        case DataType::Boolean:
            std::wcout<<((exp.t_bool)?L"true":L"false");
            break;
        case DataType::Quantity:
        case DataType::List:
        case DataType::Void:
        default:
            break;
        }

        return Data();
    }

}
