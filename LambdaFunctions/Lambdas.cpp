// This library includes the std::function, which is a general-purpose polymorphic function wrapper. It can store, copy, and invoke any callable target—functions, lambda expressions, bind expressions, or other function objects—given a matching function signature. In this code, std::function<void(int)> is used to define a type that can hold any callable that takes an int as an argument and returns void.
#include <functional>
#include <iostream>
#include <vector>

void ForEach(const std::vector<int>& values, const std::function<void(int)>& func)
{
	for (int value : values)
		func(value);
}

int main()
{
	std::vector<int> values = { 1, 2, 3, 4, 5, 6 };

	// This 'find_if' function is used for finding the first element in the range that satisfies a certain condition and returns an iterator to that element. If no such element is found, it returns an iterator to the end of the range. The condition is defined by the lambda function passed as the third argument.
	auto iterator = std::find_if(values.begin(), values.end(), [](int value)
		{
			return value > 3;
		});

	std::cout << *iterator << std::endl;

	// You can pass variables by putting them inside the '[]'. '=' passes all by value, '&' passes all by reference.
	// But if you want to pass something to the lambda function (in this case the variable 'a'), and then pass that lambda's pointer, you cannot use raw function pointer 'void (*func)(int)'.
	// The std::function comes from the 'functional' library.
	// If you want to reassign a, you have to declare lambda as mutable. '[captures](params) mutable{body}'

	int a = 5;
	// If we wanted to pass the 'a' variable by reference, we would have to use '&a' instead of 'a' in the capture list.
	auto lambda = [a](int value)
		{
			std::cout << "Value: " << value << " : " << a << std::endl;
		};
	ForEach(values, lambda);
	std::cin.get();
}