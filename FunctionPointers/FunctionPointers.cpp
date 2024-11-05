#include <iostream>
#include <vector>

void HelloWorld(int a)
{
    std::cout << "Hello World: " << a << std::endl;
}

void ForEach(const std::vector<int> &values, void (*func)(int))
{
    for (int value : values)
        func(value);
}

int main()
{
    // Gets the binary address to CPU instruction this function creates.
    auto function = &HelloWorld;
    function(5);

    // This auto type is void (*function)()
    // If you wanted to make another variable with a different name that takes a parameter -> void(*name)(parameter).
    // void(*myFunction)();
    // Mert = HelloWorld;
    // or
    // void(*myFunction)() = HelloWorld;

    typedef void (*HelloWorldFunction)(int);
    HelloWorldFunction myFunction = HelloWorld;

    myFunction(10);

    std::vector<int> values = {1, 2, 3, 4, 5};
    ForEach(values, [](int value)
            { std::cout << "Value: " << value << std::endl; });

    std::cin.get();
}