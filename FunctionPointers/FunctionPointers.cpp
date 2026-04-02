#include <iostream>
#include <vector>

void HelloWorld(int a)
{
	std::cout << "Hello World: " << a << std::endl;
}

void ForEach(const std::vector<int>& values, void (*func)(int))
{
	for (int value : values)
		func(value);
}

int main()
{
	// Gets the binary address to CPU instruction this function creates.
	auto function = &HelloWorld;
	function(5);

	// This auto type is void (*function)(int). 'function' here is just a name we give to the variable that holds the function pointer. The type of this variable is a pointer to a function that takes an int parameter and returns void.
	// If you wanted to make another variable with a different name that takes a parameter -> void(*name)(parameter type{can be left empty if the function doesn't take any parameters}).
	// void(*myFunction)(int);
	// myFunction = HelloWorld;
	// or
	// void(*myFunction)(int) = HelloWorld;
	// Then you can call it like this: myFunction();

	// Since the syntax above can be confusing, most people use either auto or typedef to make it more readable. Using auto, the compiler can deduce the type of the function pointer for you, so you don't have to write out the full type. Using typedef, you can create an alias for the function pointer type, which can make your code cleaner and easier to read.
	typedef void (*HelloWorldFunction)(int);
	HelloWorldFunction myFunction = HelloWorld;

	myFunction(10);

	std::vector<int> values = { 1, 2, 3, 4, 5 };

	// The second parameter of ForEach is a function pointer that takes an int and returns void. In this case, we are passing a lambda function that takes an int value and prints it to the console. The ForEach function will call this lambda for each element in the values vector, allowing us to print each value. The square brackets used here are part of the syntax to create a lambda function.
	ForEach(values, [](int value)
		{
			std::cout << "Value: " << value << std::endl;
		});

	std::cin.get();
}