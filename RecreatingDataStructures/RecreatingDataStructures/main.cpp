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
		std::cout << "Vector Copied!\n";
	}
	Vector3(Vector3&& other)
	{
		x = std::move(other.x);
		y = std::move(other.y);
		z = std::move(other.z);
		std::cout << "Vector Moved!\n";
	}
	~Vector3()
	{
		std::cout << "Vector Destroyed\n";
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
	Vector<Vector3> vector;
	vector.PushBack(Vector3(1.0f));
	vector.PushBack(Vector3(2, 3, 4));
	vector.PushBack(Vector3());
}

int main()
{
	std::cout << "Array Demonstrations:";
	ArrayDemonstration();
	std::cout << "===================================\n";
	std::cout << "Vector or Dynamic Array Demonstrations:\n";

}