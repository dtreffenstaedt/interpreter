#include <string>
#include <iostream>
#include <fstream>
#include <streambuf>

#include "Scanner.h"
#include "Timer.h"

int main()
{
    Scanner sc(U"test2.csc");

    Token t = sc.nextToken();

    Timer tim;
    tim.restart();
    while (t != Token::Type::End && t != Token::Type::UnexpectedEnd && t != Token::Type::Unexpected)
    {
        std::wcout<<(wchar_t)t.name()<<" : "<<(wchar_t)t.value()<<std::endl;
        t = sc.nextToken();
    }
    tim.stop();
    auto elapsed = tim.elapsed<std::chrono::nanoseconds>();
    std::cout<<elapsed.count()<<"ns elapsed"<<std::endl;
    return 0;
}
