#include <iostream>
#include <string>
static __UINT32_TYPE__ s_AllocCount = 0;

void* operator new(std::size_t count, std::align_val_t al)
{
	s_AllocCount++;
	std::cout << "Allocating " << count << " bytes\n";
	return malloc(count);
};

void PrintString(const std::string& my_string)
{
	std::cout << my_string << std::endl;
};
void PrintString(const std::string_view my_string)
{
	std::cout << my_string << std::endl;
};

int main()
{

#define ALLOC_COUNT 0

#if ALLOC_COUNT == 1
	// Depending on the compiler, strings that are smaller than a certain byte threshold are stored in the stack, thus not using the 'new' keyword.
	// In this case, the string is larger than the threshold, so it is stored in the heap, which involves memory allocation. But since this is just a string you won't be manipulating, you can turn it into a char array, which is stored in the stack and does not involve memory allocation.
	std::string name = "Peter DINKLAGE Lorem ipsum dolor sit amet, consectetur adipiscing elit. Donec dui magna, dignissim sed convallis et, feugiat vel libero. Fusce eget mi consequat, lacinia lectus vel, suscipit urna. Nam elit sapien, lacinia nec nisi in, fermentum rutrum justo. Nam quis quam metus. Nullam lacinia, dui vitae congue iaculis, leo ex condimentum.";
	PrintString(name);
	std::cout << s_AllocCount << " allocations\n";


	// The substr method creates a new string object, which involves memory allocation, while string_view does not create a new string object and thus does not involve memory allocation.
	std::string firstName = name.substr(0, 5);
	std::string lastName = name.substr(5, 8);
	PrintString(firstName);
	std::cout << s_AllocCount << " allocations\n";

	// The string_view constructor creates a view into the original string without copying it, so it does not involve memory allocation. It simply points to the existing string data, allowing you to access a portion of the string without creating a new string object.
	std::string_view firstName(name.c_str(), 5);
	std::string_view lastName(name.c_str() + 6, 8);

	PrintString(firstName);
	std::cout << s_AllocCount << " allocations\n";

#else if ALLOC_COUNT == 0
	// Using a char array instead of a string to avoid memory allocation, and using string_view to create views into the char array without copying it, thus avoiding memory allocation completely.
	const char* name = "Peter Dinklage";
	std::string_view firstName_view(name, 5);
	std::string_view lastName_view(name + 6, 8);

	PrintString(firstName_view);
	PrintString(lastName_view);

	std::cout << s_AllocCount << " allocations" << std::endl;
#endif


	std::cin.get();
}