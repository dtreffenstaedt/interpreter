#include <string>
#include <iostream>
#include <fstream>
#include <streambuf>

#include "Scanner.h"
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
    Scanner sc(file.c_str());

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
    auto elapsed = tim.elapsed<std::chrono::nanoseconds>();
    tim.stop();

    while (!queue.empty())
    {
        t = queue.get();
        std::wcout<<t.name()<<" : "<<t.value()<<"\n";
    }
    std::wcout<<elapsed.count()<<"ns elapsed\n";
    return 0;
}
