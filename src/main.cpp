#include <string>
#include <iostream>
#include <fstream>
#include <streambuf>

#include "Scanner.h"
#include "Timer.h"

int main()
{   
    std::setlocale(LC_ALL, "en_US.UTF8");
    Scanner sc("test2.csc");

    Token t = sc.nextToken();

    Timer tim;
    tim.restart();
    while (t != Token::Type::End && t != Token::Type::UnexpectedEnd && t != Token::Type::Unexpected)
    {
        std::wcout<<t.name()<<" : "<<t.value()<<"\n";
        t = sc.nextToken();
    }
    tim.stop();
    auto elapsed = tim.elapsed<std::chrono::nanoseconds>();
    std::cout<<elapsed.count()<<"ns elapsed\n";
    return 0;
}
