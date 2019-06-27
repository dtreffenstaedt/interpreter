#include <string>
#include <iostream>
#include <fstream>
#include <streambuf>

#include "Scanner.h"
#include "Parser.h"
#include "Timer.h"

int main(int argc, char* argv[])
{   
    std::setlocale(LC_ALL, "en_US.UTF8");
    std::string file = "test2.csc";

    if (argc == 2)
    {
        file = argv[1];
    }
    std::wcout<<"opening "<<file.c_str()<<"\n";
//    Scanner sc(file.c_str());

    Parser p(file.c_str());

    Timer tim;
    tim.restart();
    p.run();

    auto elapsed = tim.count<std::chrono::nanoseconds>();
    tim.stop();
/*
    Token t = sc.nextToken();

    Queue<Token> queue;

    Timer tim;
    tim.restart();
    while (t != Token::Type::End && t != Token::Type::UnexpectedEnd && t != Token::Type::Unexpected)
    {
        queue<<t;
        t = sc.nextToken();
    }
    queue<<t;
    auto elapsed = tim.count<std::chrono::nanoseconds>();
    tim.stop();

    while (!queue.empty())
    {
        t = queue.get();
        std::wcout<<t.name()<<" : "<<t.value()<<"\n";
    }*/
    std::wcout<<elapsed<<"ns elapsed\n";
    return 0;
}
