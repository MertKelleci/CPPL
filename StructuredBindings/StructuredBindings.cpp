#include <iostream>
#include <string>
#include <tuple>

std::tuple<std::string, int> CreatePerson()
{
    return {"Person", 24};
}

int main()
{
    // A tuple can be used to return multiple variables with different types.
    // auto person = CreatePerson();
    // std::string& name = std::get<0>(person);
    // int age = std::get<1>(person);

    // std::string name;
    // int age;
    // std::tie(name, age) = CreatePerson();

    // This feature is only for C++ 17 and above.
    auto [name, age] = CreatePerson();
    std::cout << name << std::endl;

    std::cin.get();
}