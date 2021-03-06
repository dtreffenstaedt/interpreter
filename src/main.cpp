#include <string>
#include <iostream>
#include <fstream>
#include <streambuf>

#include "Scanner.h"
#include "Parser.h"
#include "Timer.h"

#include "FunctionManager.h"

int main(int argc, char* argv[])
{   
    std::setlocale(LC_ALL, "en_GB.UTF8");
    std::string file = "example.csc";

    if (argc == 2)
    {
        file = argv[1];
    }
    else
    {
        std::wcout<<"No filename specified. bye.\n";
        return 0;
    }

    Parser p(file.c_str());

    Timer tim;
    tim.restart();
    try
    {
        std::shared_ptr<AST::Base> root = p.parse();
        root->execute(std::make_shared<FunctionManager>(FunctionManager()), std::make_shared<VariableManager>(VariableManager()));
    }
    catch (UnexpectedToken& e)
    {
        e.print();
        return -1;
    }

    auto elapsed = tim.count<std::chrono::nanoseconds>();
    tim.stop();
    std::wcout<<L"\n"<<elapsed<<L"ns elapsed\n";
    return 0;
}
