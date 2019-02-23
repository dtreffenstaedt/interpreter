#include <string>
#include <iostream>

#include "Scanner.hpp"

int main()
{
    std::string test = "print(\"ab\nc\"); // this is a comment\nint a = 5;\na += 3;\nchar c = 'd';";
    std::cout<<test<<std::endl;
    Scanner sc(test);

    Token t = sc.nextToken();

    while (t != Token::Type::End)
    {
        std::cout<<t.name()<<" : "<<t.value()<<std::endl;
        t = sc.nextToken();
    }

    return 0;
}
