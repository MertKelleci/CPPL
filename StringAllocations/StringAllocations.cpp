#include <iostream>
#include <string>
static __UINT32_TYPE__ s_AllocCount = 0;

void *operator new(std::size_t count, std::align_val_t al)
{
    s_AllocCount++;
    std::cout << "Allocating " << count << " bytes\n";
    return malloc(count);
};

void PrintString(const std::string &my_string)
{
    std::cout << my_string << std::endl;
};
void PrintString(const std::string_view my_string)
{
    std::cout << my_string << std::endl;
};

int main()
{
    // Depending on the compiler, strings that are smaller than a certain byte threshold are stored in the stack, thus not using the 'new' keyword.
    std::string name = "Peter DINKLAGE this part of the string is inserted due to reasons mentioned above Peter DINKLAGE this part of the string is inserted due to reasons mentioned above Peter DINKLAGE this part of the string is inserted due to reasons mentioned above Peter DINKLAGE this part of the string is inserted due to reasons mentioned above Peter DINKLAGE this part of the string is inserted due to reasons mentioned above Peter DINKLAGE this part of the string is inserted due to reasons mentioned above Peter DINKLAGE this part of the string is inserted due to reasons mentioned above";
    PrintString(name);
    std::cout << s_AllocCount << " allocations\n";

    std::string firstName = name.substr(0, 5);
    std::string lastName = name.substr(5, 8);
    PrintString(firstName);
    std::cout << s_AllocCount << " allocations\n";

    std::string_view firstName(name.c_str(), 5);
    std::string_view lastName(name.c_str() + 6, 8);
    std::cout << s_AllocCount << " allocations\n";

    std::cin.get();
}