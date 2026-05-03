#include <expected>
#include <iostream>

std::expected<int, std::string> divide(int a, int b)
{
	if (b == 0)
	{
		return std::unexpected("Division by zero");
	}
	return a / b;
}

int main()
{
	auto result1 = divide(10, 0);
	if (result1)
		std::cout << "Result: " << *result1 << std::endl;
	else
		std::cerr << "Error: " << result1.error() << std::endl;

	auto result2 = divide(10, 2);
	if (result2)
		std::cout << "Result: " << *result2 << std::endl;
	else
		std::cerr << "Error: " << result2.error() << std::endl;

	std::cin.get();
}