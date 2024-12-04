#include <iostream>

struct Entity
{
    operator float() { return 6.9; }
};

void PrintFloat(float myFloat)
{
    std::cout << myFloat << std::endl;
}

int main()
{
    Entity e;
    float f = e;

    std::cout << f << std::endl;
    PrintFloat(e);
    std::cin.get();
}