#include "Array.h"
#include "DynamicArray.h"
#include <iostream>

struct Vector3
{
	float x = 0.0f, y = 0.0f, z = 0.0f;
	Vector3() {}
	Vector3(float scalar) : x(scalar), y(scalar), z(scalar) {}
	Vector3(float x, float y, float z) : x(x), y(y), z(z) {}
	Vector3(const Vector3& other) : x(other.x), y(other.y), z(other.z)
	{
		std::cout << "Vector3 Copied!\n";
	}
	Vector3(Vector3&& other) noexcept
	{
		x = std::move(other.x);
		y = std::move(other.y);
		z = std::move(other.z);
		std::cout << "Vector3 Moved!\n";
	}
	~Vector3()
	{
		std::cout << "Vector3 Destroyed\n";
	}
	Vector3& operator=(const Vector3& other)
	{
		std::cout << "Vector3 Copied\n";
		x = other.x;
		y = other.y;
		z = other.z;
		return *this;
	}
	Vector3& operator=(const Vector3&& other) noexcept
	{
		std::cout << "Vector3 Moved\n";
		x = other.x;
		y = other.y;
		z = other.z;
		return *this;
	}
};

void ArrayDemonstration()
{
	Array<int, 5> data;
	//This 'static_assert' function is used to make sure the size of the Array isn't bigger than 10. We are able to use the 'array.Size' function because it's declared a 'constexpr'.
	static_assert(data.Size() < 10, "Size too large.");

	memset(data.Data(), 0, data.Size() * sizeof(int));
	for (size_t i = 0; i < data.Size(); i++)
		std::cout << data[i] << std::endl;

	std::cout << "-----------------------\n";

	data[1] = 3;
	data[2] = 5;

	for (size_t i = 0; i < data.Size(); i++)
		std::cout << data[i] << std::endl;
}

void VectorDemonstration()
{
	/*Vector<Vector3> vector;
	vector.PushBack(Vector3(1.0f));
	vector.PushBack(Vector3(2, 3, 4));
	vector.PushBack(Vector3());*/

	Vector<int> values;

	values.EmplaceBack(1);
	values.EmplaceBack(3);
	values.EmplaceBack(5);
	values.EmplaceBack(2);
	values.EmplaceBack(9);

	std::cout << "Not using iterator:\n";
	for (int i = 0; i < values.Size(); i++)
		std::cout << values[i] << " ";
	std::cout << std::endl;


	std::cout << "Range based for loop:\n";
	for (int value : values)
		std::cout << value << " ";
	std::cout << std::endl;

	std::cout << "Iterator:\n";
	for (Vector<int>::Iterator it = values.begin(); it != values.end(); it++)
		std::cout << *it << " ";
	std::cout << std::endl;

}

int main()
{
	/*std::cout << "Array Demonstrations:";
	ArrayDemonstration();
	std::cout << "===================================\n";*/
	std::cout << "Vector or Dynamic Array Demonstrations:\n";
	VectorDemonstration();

}