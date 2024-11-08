#include <iostream>
#include <variant>

int main()
{
    std::variant<std::string, int> data;
    data = "My Data";
    data.index(); // 0
    std::cout << std::get<std::string>(data) << "\n";
    data = 2;

    auto *value = std::get_if<std::string>(&data);
    if (value)
    {
        std::string &v = *value;
    }

    std::cout << sizeof(int) << "\n";
    std::cout << sizeof(std::string) << "\n";
    std::cout << sizeof(data) << "\n";

    data.index(); // 1
    std::cout << std::get<int>(data) << "\n";
    std::cin.get();
}