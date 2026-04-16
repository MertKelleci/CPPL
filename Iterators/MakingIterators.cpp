#include "Vector.h"
#include <iostream>

int main()
{
	Vector<int> values;
	values.PushBack(1);
	values.PushBack(2);
	values.PushBack(3);

	std::cout << "Not using iterators:\n";
	for (size_t i = 0; i < values.Size(); i++)
		std::cout << values[i] << " ";
	std::cout << std::endl;


	std::cout << "Using iterators in range-based for loop:\n";
	for (auto& value : values)
		std::cout << value << " ";
	std::cout << std::endl;

	std::cout << "Using iterators in a traditional for loop:\n";
	for (Vector<int>::Iterator it = values.begin(); it != values.end(); it++)
		std::cout << *it << " ";
	std::cout << std::endl;

	std::cin.get();
}

