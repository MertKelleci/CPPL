#include <iostream>

// This is an lvalue reference. lvalues are objects that have a name and a memory address. They can be assigned to and they can be passed by reference.
void PrintName(const std::string& name)
{
	// PrintName(fullname) calls this function.
	std::cout << "[lvalue] " << name << std::endl;
}

// This is an rvalue reference. rvalues are temporary values.
// Lets say we have a function like this: 'function(int& value)'. Here the 'int& value' takes an lvalue. So 'function(10)' won't work whereas 'function(i)' does. Since pointers, references and assignments are lvalues.
void PrintName(const std::string&& name)
{
	// PrintName(firstname + lastname) calls this function.
	std::cout << "[rvalue] " << name << std::endl;
}

int main()
{
	// i = lvalue, 10 = rvalue
	// 'i' is a variable, it has a memory address and you can get its reference. 10 is just a value, a numeric literal, it doesn't have a memory address, no storage and you can't get its reference. That is untill you assign it to a lvalue.
	int i = 10;

	// The assingment below won't work because you can't get the lvalue of an rvalue. 10 is just a numerical value and it doesn't have a memory address and therefore you can't get its reference.
	// int& a = 10;

	// If you declare it const you can get its reference because in the backend, compiler creates a temporary variable and assings that value to this variable and then declares that a const.
	// So 'function(const type& value)' accepts both lvalues and rvalues.
	const int& a = 10;

	// The values to the right of the assignment operator are rvalues. They are temporary values that don't have a name and they don't have a memory address. They are just values that are used in expressions and they are not stored in memory. The values to the left of the assignment operator are lvalues. They are objects that have a name and a memory address. They can be assigned to and they can be passed by reference.
	std::string firstname = "Peter";
	std::string lastname = "Dinklage";

	std::string fullname = firstname + lastname;

	// The function 'PrintName' is overloaded. It has two versions, one that takes a const reference and one that takes an rvalue reference. When we call 'PrintName(fullname)', the compiler will choose the version that takes a const reference because 'fullname' is an lvalue. When we call 'PrintName(firstname + lastname)', the compiler will choose the version that takes an rvalue reference because 'firstname + lastname' is an rvalue.
	PrintName(fullname);
	PrintName(firstname + lastname);
	std::cin.get();
}