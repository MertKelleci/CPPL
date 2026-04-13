#include <iostream>;

template<typename T, size_t S >
class Array
{
public:
	// The 'const' ensures we don't modify the class. The 'constexpr' allows the function to be evaluated at compile time, which is necessary for static_assert to work. It also allows you to create other Arrays using another Arrays size as a template parameter.
	constexpr size_t Size() const { return S; }

	// If this function didn't return a reference, it would return a copy of the value at index i, which means that any modifications to the returned value would not affect the original array. By returning a reference, we can modify the original array directly through the returned reference.
	T& operator[](size_t i) { return m_Data[i]; }

	// This is an overloaded version of the operator[] for const objects. It allows us to access the elements of the array without modifying them. If we try to modify the returned value, it will result in a compile-time error because the function is marked as const. Without this function, we would not be able to access the elements of the array if we have a const instance of the Array class, even if we didn't manipulate the data like we did when we print the values to the console, which would limit the usability of the class.
	const T& operator[](size_t i) const { return m_Data[i]; }

	T* Data() { return m_Data; }
	const T* Data() const { return m_Data; }
private:
	T m_Data[S];

};

int main()
{
	// You can't dynamically create this array with a size variable, unless said variable is declared as constexpr, which means that it is a compile-time constant.
	Array<int, 5> arr;

	// static_assert is a compile-time assertion. It checks the condition at compile time and if it fails, it generates a compile-time error with the provided message.
	static_assert(arr.Size() < 10, "Size is too large");

	for (int i = 0; i < arr.Size(); i++)
	{
		arr[i] = i;
		std::cout << arr[i] << std::endl;
	}

	const auto& arr2 = arr;

	memset(arr.Data(), 0, arr.Size() * sizeof(int));
	for (int i = 0; i < arr.Size(); i++)
	{
		//arr2[i] = i;
		std::cout << arr2[i] << std::endl;
	}

	std::cin.get();
}
