#include <iostream>
#include <string>

template <typename T>
void Print(T value)
{
    std::cout << value << std::endl;
}

template <typename T>
T add(T a, T b)
{
    return a + b;
}

template <typename T, int N>
class Array
{
private:
    T m_Array[N];

public:
    int Getsize() const { return N; }
};

int main()
{
    Print(5);
    Print("Hello World");

    double a = add(5.0f, 2.5f);
    int b = add(2, 3);

    // This one won't work.
    // std::string c = add("Hello ", "World");
    // While this one does. Because if you call the function without angle brackets, any ambiguous or non-deducible types will create problems.
    // In this example, two parameters we send can either be 'std::string', which support '+' operation, or char pointer, which doesn't support '+' operation.
    std::string c = add<std::string>("Hello ", "World");

    std::cout << c << std::endl;

    Array<int, 5> array;
    std::cout << array.Getsize() << std::endl;

    std::cin.get();
}