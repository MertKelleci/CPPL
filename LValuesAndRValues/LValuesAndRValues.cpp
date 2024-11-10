#include <iostream>

void PrintName(const std::string &name)
{
    std::cout << "[lvalue] " << name << std::endl;
}

// This is an rvalue reference. rvalues are temporary values.
// 'function(int& value)' here the 'int& value' takes a rvalue. So 'function(10)' won't work whereas 'function(i)' does. Since pointers, references and assignments are lvalues.
void PrintName(const std::string &&name)
{
    std::cout << "[rvalue] " << name << std::endl;
}

int main()
{
    // i = lvalue, 10 = rvalue
    int i = 10;
    // The assingment below won't work because you can't get the lvalue of an rvalue. 10 is just a numerical value and it doesn't have a memory address and therefore you can't get its reference.
    // int& a = 10;

    // If you declare it const you can get its reference because in the backend, compiler creates a temporary variable and assings that value to this variable and then declares that a const.
    // So 'function(const type& value)' accepts both lvalues and rvalues.
    const int &a = 10;

    std::string firstname = "Peter";
    std::string lastname = "Dinklage";

    std::string fullname = firstname + lastname;

    PrintName(fullname);
    PrintName(firstname + lastname);
    std::cin.get();
}