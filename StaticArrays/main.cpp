#include <array>
#include <iostream>

int main()
{
	// std::array is a container that encapsulates fixed size arrays. It is a wrapper around a raw array and provides a more convenient and safer interface for working with arrays in C++. The size of the array is determined at compile time and cannot be changed at runtime. Unlike normal arrays, std::array provides member functions such as size(), fill(), and swap(), which make it easier to work with arrays. Additionally, std::array supports iterators, allowing you to use range-based for loops and other standard algorithms. Overall, std::array is a useful container for situations where you need a fixed-size array with additional functionality and safety features compared to raw arrays.
	std::array<int, 5> data = { 1,2,3,4,5 };
	data[0] = 6;
	std::cin.get();
}