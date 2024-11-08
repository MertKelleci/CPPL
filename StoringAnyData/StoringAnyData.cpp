#include <iostream>
#include <any>

int main()
{
    std::any data;
    data = 2;
    data = "const char pointer";
    data = std::string("String");

    std::string &dataString = std::any_cast<std::string &>(data);
    std::cin.get();
}