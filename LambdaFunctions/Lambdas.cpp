#include <iostream>
#include <vector>
#include <functional>

void ForEach(const std::vector<int> &values, const std::function<void(int)> &func)
{
    for (int value : values)
        func(value);
}

int main()
{
    std::vector<int> values = {1, 2, 3, 4, 5, 6};
    auto it = std::find_if(values.begin(), values.end(), [](int value)
                           { return value > 3; });

    std::cout << *it << std::endl;

    // You can pass variables by putting them inside the '[]'. '=' passes all by value, '&' passes all by reference.
    // But if you want to pass something and then pass that lambda's pointer, you cannot use raw function pointer 'void (*func)(int)'.
    // The std::function comes from the 'functional' library.
    // If you want to reassign a, you have to declare lambda as mutable. '[captures](params) mutable{body}'

    int a = 5;
    auto lambda = [a](int value)
    { std::cout << "Value: " << value << " : " << a << std::endl; };
    ForEach(values, lambda);
    std::cin.get();
}