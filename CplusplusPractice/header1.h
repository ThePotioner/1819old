#include <iostream>

namespace header1
{
    int foo()
    {
        std::cout << "This is H1 - foo()" << std::endl;

        return 0;
    }
    void bar()
    {
        std::cout << "This is H1 - bar()" << std::endl;
    }
}