#include <iostream>

namespace header2
{
    int foo()
    {
        std::cout << "This is H2 - foo()" << std::endl;

        return 0;
    }
    void bar()
    {
        std::cout << "This is H2 - bar()" << std::endl;
    }
}