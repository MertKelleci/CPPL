#include<iostream>
#include<string>

template<typename T>
class Vector
{
public:
	Vector()
	{
		ReAlloc(2);
	}

	~Vector()
	{
		Clear();
		::operator delete(m_Data, m_Capacity * sizeof(T));
	}

	void PushBack(const T& value)
	{
		if (m_Size >= m_Capacity)
			ReAlloc(m_Capacity + m_Capacity / 2);
		m_Data[m_Size] = value;
		m_Size++;
	}

	void PushBack(T&& value)
	{
		if (m_Size >= m_Capacity)
			ReAlloc(m_Capacity + m_Capacity / 2);
		m_Data[m_Size] = std::move(value);
		m_Size++;
	}

	// The EmplaceBack function is a variadic template function that allows us to construct an object in place in the vector. It takes a variable number of arguments and forwards them to the constructor of the object being emplaced. This can be more efficient than creating a temporary object and then moving it into the vector, especially if the object has a non-trivial constructor or if it is large.
	template<typename... Args>
	T& EmplaceBack(Args&&... args)
	{
		if (m_Size >= m_Capacity)
			ReAlloc(m_Capacity + m_Capacity / 2);

		// The triple dot here allows us to unpack these arguments so the constructor works as expected. For example, if we call EmplaceBack(1, 2, 3), the arguments will be forwarded to the constructor of the object as if we had called T(1, 2, 3) directly. This allows us to construct the object in place without having to create a temporary object first, which can be more efficient.

		// The following still generates a temporary object and then move it to the vector.
		//m_Data[m_Size] = T(std::forward<Args>(args)...);

		// So a better way to fill the vector would be to directly created the data inside the already allocated memory, which is what the placement new operator does. It allows us to construct an object in a pre-allocated memory buffer. By using placement new, we can avoid the overhead of creating a temporary object and then moving it into the vector, which can be more efficient, especially for large objects or objects with non-trivial constructors.
		new(&m_Data[m_Size]) T(std::forward<Args>(args)...);
		return m_Data[m_Size++];
	}

	void PopBack()
	{
		if (m_Size > 0)
		{
			m_Size--;
			m_Data[m_Size].~T();
		}
	}

	void Clear()
	{
		for (size_t i = 0; i < m_Size; i++)
			m_Data[i].~T();
		m_Size = 0;
	}

	const T& operator[](size_t index) const
	{
		return m_Data[index];
	}

	T& operator[](size_t index)
	{
		return m_Data[index];
	}

	size_t Size() const
	{
		return m_Size;
	}

private:
	T* m_Data = nullptr;
	size_t m_Size = 0;
	size_t m_Capacity = 0;

	void ReAlloc(size_t newCapacity)
	{

		std::cout << "ReAllocating to " << newCapacity << " from " << m_Capacity << std::endl;

		// The following code will cause problems when you do a bunch of PopBacks and Clears because the program will try to delete memory that has already been deleted, which can lead to undefined behavior.
		//T* newBlock = new T[newCapacity];

		T* newBlock = (T*)::operator new(newCapacity * sizeof(T));

		// This if statement checks if we are downsizing the vector.
		if (newCapacity < m_Size)
			m_Size = newCapacity;

		// The reason why we don't use a function like memcpy is because it doesn't call the copy constructor of the objects, which can lead to undefined behavior if the objects have non-trivial copy constructors. If the vector contains only primitive types, using memcpy would be fine, but more complex types may require to do allocations of their own, and memcpy would not handle that correctly.

		// The following would copy the elements in the array, but we want them to be moved to increase the efficiency of the operation, especially if the objects are large or have expensive copy constructors. By using std::move, we can transfer ownership of the resources from the old array to the new one without having to create temporary copies of the objects.
		//for (size_t i = 0; i < m_Size; i++)
		//	newBlock[i] = m_Data[i];
		for (size_t i = 0; i < m_Size; i++)
			newBlock[i] = std::move(m_Data[i]);

		for (size_t i = 0; i < m_Size; i++)
			m_Data[i].~T();

		//delete[] m_Data;

		::operator delete(m_Data, m_Capacity * sizeof(T));
		m_Data = newBlock;
		m_Capacity = newCapacity;
	}
};

struct Vector3
{
	float x = 0.0f, y = 0.0f, z = 0.0f;
	Vector3() {};
	Vector3(float scalar) : x(scalar), y(scalar), z(scalar) {};
	Vector3(float x, float y, float z) : x(x), y(y), z(z) {};

	// Copy constructor.
	Vector3(const Vector3& other) : x(other.x), y(other.y), z(other.z)
	{
		std::cout << "Vector Copied\n";
	}

	// Move constructor.
	Vector3(const Vector3&& other) : x(other.x), y(other.y), z(other.z)
	{
		std::cout << "Vector Moved\n";
	}

	// Destructor.
	~Vector3()
	{
		std::cout << "Vector Destroyed\n";
	}

	Vector3& operator=(const Vector3& other)
	{
		std::cout << "Vector Copy Assigned\n";
		x = other.x;
		y = other.y;
		z = other.z;
		return *this;
	}

	Vector3& operator=(const Vector3&& other)
	{
		std::cout << "Vector Move Assigned\n";
		x = other.x;
		y = other.y;
		z = other.z;
		return *this;
	}
};

std::ostream& operator<<(std::ostream& os, const Vector3& vector)
{
	os << "Vector3(" << vector.x << ", " << vector.y << ", " << vector.z << ")";
	return os;
}

template<typename T>
void PrintVector(const Vector<T>& vector)
{
	for (size_t i = 0; i < vector.Size(); i++)
		std::cout << vector[i] << " ";
	std::cout << std::endl;
}

int main()
{
	Vector<Vector3> vector;
	//vector.PushBack(1.0f);
	//vector.PushBack((2, 3, 4));
	//vector.PushBack(Vector3());

	vector.EmplaceBack(1.0f);
	vector.EmplaceBack(2, 3, 4);
	vector.EmplaceBack(5, 6, 7);
	vector.EmplaceBack(8, 9, 1);
	PrintVector(vector);
	vector.PopBack();
	vector.PopBack();
	vector.PopBack();
	PrintVector(vector);

	vector.EmplaceBack(2.0f);
	vector.EmplaceBack(3.0f);
	vector.EmplaceBack(4.0f);
	PrintVector(vector);

	vector.Clear();
	vector.EmplaceBack(0.0f);

	PrintVector(vector);
	std::cin.get();
}