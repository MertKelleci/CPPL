#include <iostream>

struct Vector2
{
	float x, y;
};
struct Vector4
{
	// float x, y, z, w;

	// One way to get Vector2 out of Vector4.
	// Vector2 &GetA()
	// {
	//     return *(Vector2 *)&x;
	// }

	// What union does in this instance is that it allows us to treat the same memory as either a struct of 4 floats or as a struct of 2 Vector2s. This means that when we access vector.a, we are actually accessing the first two floats (x and y), and when we access vector.b, we are accessing the next two floats (z and w). This is a convenient way to group related data together without needing to define separate structures for each case.
	union
	{
		struct
		{
			float x, y, z, w;
		};
		struct
		{
			Vector2 a, b;
		};
	};
};

void PrintVector2(const Vector2& vector)
{
	std::cout << vector.x << ", " << vector.y << std::endl;
}

int main()
{
	Vector4 vector = {
		1.0f,
		2.0f,
		3.0f,
		4.0f,
	};

	PrintVector2(vector.a);
	PrintVector2(vector.b);
	vector.z = 500.0f;
	vector.x = 250.0f;
	std::cout << "=======================" << std::endl;
	PrintVector2(vector.a);
	PrintVector2(vector.b);
	std::cin.get();
}