#include <iostream>
class Base
{
public:
    Base() { std::cout << "Base Constructor\n"; }
    virtual ~Base() { std::cout << "Base Destructor\n"; }
};

class Derived : public Base
{
public:
    Derived() { std::cout << "Derived Constructor\n"; }
    ~Derived() { std::cout << "Derived Destructor\n"; }
};

int main()
{
    Base *base = new Base();
    delete base;
    std::cout << "----------------\n";

    Derived *derived = new Derived();
    delete derived;
    std::cout << "----------------\n";

    // This doesn't trigger the Derived destructor, if the Base destructor is declared virtual.
    // If you want a class to be inherited, you should declare the base class's destructor as virtual. If not, you could cause a memory leak.
    Base *poly = new Derived();
    delete poly;
    std::cin.get();
}