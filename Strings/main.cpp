#include <iostream>
#include <string>

void PrintString(const std::string &string)
{
    std::cout << string << std::endl;
}

int main()
{
    // Characters are defined with singlue quote, if double quote used its automatically defaults to char pointer
    const char *name = "Merdo";
    // This will keep printing until it comes across a byte with 00. You can manually add to stop with either 0 or '\0'
    char name2[7] = {'C', 'h', 'e', 'r', 'n', 'o', 0};

    // To append strings, either:
    // std::string name3 = "something"
    // name3 += "something else"
    // OR
    // std::string name3 = std::string("something") + "something else"
    std::string name3 = "Cherno";

    bool contains = name3.find("no") != std::string::npos;
    std::cout << &name3 << std::endl;
    PrintString(name3);
    std::cin.get();
}