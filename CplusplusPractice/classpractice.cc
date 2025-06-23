#include <string>
#include <iostream>

class Test
{
    std::string str;

    public:
        Test(std::string _str)
        {
            str = _str;
            std::cout << "생성자 호출! " << str << std::endl;
        }
        ~Test()
        {
            std::cout << "소멸자 호출! " << str << std::endl;
        }
};

class Foo
{
    int number;

    public:
        Foo(int inp) : number(inp) {}

        int& accessNumber() { return number; }
        int getNumber() { return number; }
        void showNumber() { std::cout << number << std::endl; }
};

void simpleFunction()
{
    Test B("B Class");
}

int main()
{
    // Test A("A Class");
    // simpleFunction();

    Foo a(5);
    a.showNumber();

    int& c = a.accessNumber();
    c = 4;
    a.showNumber();

    int d = a.accessNumber();
    d = 3;
    a.showNumber();

    int f = a.getNumber();
    f = 1;
    a.showNumber();
}