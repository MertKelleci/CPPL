#include <iostream>
#include <unordered_map>
#include <vector>

int main()
{
	std::vector<int> values = { 1, 2, 3, 4, 5 };

	for (int i = 0; i < values.size(); i++)
		std::cout << values[i] << " ";
	std::cout << std::endl;

	for (int value : values)
		std::cout << value << " ";
	std::cout << std::endl;


	for (std::vector<int>::iterator it = values.begin(); it != values.end(); it++)
		std::cout << *it << " ";
	std::cout << std::endl;

	std::unordered_map<std::string, int> map = { {"one", 1}, {"two", 2}, {"three", 3} };


	using MapIterator = std::unordered_map<std::string, int>;
	for (MapIterator::const_iterator it = map.begin(); it != map.end(); it++)
	{
		auto& [key, value] = *it;
		std::cout << key << ": " << value << std::endl;
	}

	std::cout << "=====================================" << std::endl;

	for (auto mapPair : map)
	{
		auto& [key, value] = mapPair;
		std::cout << key << ": " << value << std::endl;
	}

	std::cout << "=====================================" << std::endl;

	for (auto [key, value] : map)
	{
		std::cout << key << ": " << value << std::endl;
	}

	std::cin.get();
}

