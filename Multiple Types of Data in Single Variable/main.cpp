#include <iostream>
#include <variant>

int main()
{
	std::variant<std::string, int> data;
	data = "Hello, World!";

	std::cout << std::get<std::string>(data) << std::endl;
	data = 42;

	std::cout << std::get<int>(data) << std::endl;

	//std::cout << std::get<std::string>(data) << std::endl;
	// Attempting to access the wrong type will throw a bad_variant_access exception. You can catch it to handle the error gracefully.

	// Or you can use a function called 'index' to check which type is currently held by the variant before accessing it.

	std::cout << "Current index: " << data.index() << std::endl;
	// The index of the currently held type can be used to determine which type is active in the variant. In this example, the index will be 0 for std::string and 1 for int.

	// You can also use std::get_if to safely access the value without throwing an exception. It returns a pointer to the value if the type matches, or nullptr if it doesn't.
	auto* value = std::get_if<std::string>(&data);

	// Variant takes up as much memory as the types it can be. So unions are much more efficient in terms of memory usage, but they require manual management of the active member and can lead to undefined behavior if not used carefully. Variants, on the other hand, handle type safety and memory management automatically, making them safer and easier to use at the cost of potentially increased memory usage.
	std::cout << "Size of std::string: " << sizeof(std::string) << " bytes" << "\n";
	std::cout << "Size of int: " << sizeof(int) << " bytes" << "\n";
	std::cout << "Size of variant: " << sizeof(data) << " bytes" << std::endl;

	std::cin.get();
}