#include <iostream>
#include <string>

void PrintString(const std::string &string)
{
    std::cout << string << std::endl;
}

int main()
{
    // Characters are defined with singlue quote, if double quote used its automatically defaults to char pointer
    const char* name = "Merdo";
    // The following isn't actually a char pointer, but a char array. If you were to print this without the 0 at the end, it would keep printing until it comes across a byte with 00. You can manually add to stop with either 0 or '\0'
    char name2[7] = {'C', 'h', 'e', 'r', 'n', 'o', 0};

    // To append strings, either:
    // std::string name3 = "something"
    // name3 += "something else"
    // OR
    // std::string name3 = std::string("something") + "something else"
    std::string name3 = "Cherno";
    
	//std::string::npos is a constant that represents the maximum value for size_t, which is typically used to indicate that a substring was not found in a string.When you call the find() method on a string, it returns the position of the first occurrence of the specified substring.If the substring is not found, it returns std::string::npos.
    bool contains = name3.find("no") != std::string::npos;

	// Since PrintString method doesn't change the string, we can pass it by reference to avoid unnecessary copying of the string. This is more efficient, especially for larger strings.
    std::cout << &name3 << std::endl;
    PrintString(name3);
    std::cin.get();
}