#include <iostream>
#include <string.h>

class String
{
public:
	String() = default;
	String(const char* string)
	{
		printf("Created\n");
		m_Size = strlen(string);
		m_Data = new char[m_Size];
		memcpy(m_Data, string, m_Size);
	}
	String(const String& string) : m_Size(string.m_Size)
	{
		printf("Copied\n");
		m_Data = new char[m_Size];
		memcpy(m_Data, string.m_Data, m_Size);
	}

	// There are lots of cases where we want to move the data instead of copying it, for example when we are creating a temporary string and we want to move it into an Entity instance, or when we want to pass an object to a function. By default, C++ will try to copy the data, but if we want to move it, we can use a move constructor and a move assignment operator. The move constructor and move assignment operator are special member functions that are called when an object is being moved instead of copied. This feature was added in C++11 with rvalue references. The following code is an example of a move constructor and a move assignment operator for the String class.
	String(String&& string)
	{
		printf("Moved\n");
		m_Size = string.m_Size;
		// Instead of copying, we get the pointer of the original data.
		m_Data = string.m_Data;

		// The reason for this is when the previous String instance is deleted, we don't lose the 'm_Data'. So when you create a move constructor, you have to turn other string into a hollow object like this.
		string.m_Size = 0;
		string.m_Data = nullptr;
	}

	// This overloads the assignment operator to move the data instead of copying it. The move assignment operator is called when an object is being assigned to another object that is already constructed. The move assignment operator is similar to the move constructor, but it also has to check if the object is being assigned to itself, and it has to delete the existing data before moving the new data.
	String& operator=(String&& string)
	{
		printf("Moved\n");

		// This if statement checks if the String instance isn't being assigned to itself.
		if (this != &string)
		{
			// We have to delete the existing data before moving the new data, otherwise we would have a memory leak since you might already have some data stored in this String object.
			delete[] m_Data;
			m_Size = string.m_Size;
			// Instead of copying, we get the pointer of the original data.
			m_Data = string.m_Data;

			// The reason for this is the same with why we do it in the move constructor.
			string.m_Size = 0;
			string.m_Data = nullptr;
		}

		return *this;
	}
	~String()
	{
		printf("Destroyed\n");
		delete m_Data;
	}

	void Print()
	{
		for (__UINT32_TYPE__ i = 0; i < m_Size; i++)
			printf("%c", m_Data[i]);

		printf("\n");
	}

private:
	char* m_Data;
	__UINT32_TYPE__ m_Size;
};

class Entity
{
public:
	Entity(const String& name) : m_Name(name)
	{}
	// This constructor changed from taking a reference to taking a rvalue reference, in order to move the string instead of copying it. You have to explicitly cast it as a rvalue reference for this to call correct String constructor. To do that, you either call the std::move function or you can do a static cast to a rvalue reference like this: '((String&&)string)'.
	Entity(String&& name) : m_Name(std::move(name))
	{}

	void PrintName() { m_Name.Print(); }

private:
	String m_Name;
};

int main()
{
	// Without the move semantics, you would first create a temporary string and allocate memory for it, then copy the string into the Entity instance and allocate memory for it again, and then delete the temporary string and free the memory. With move semantics, you can create a temporary string and move it into the Entity instance without copying it, which is more efficient.
	Entity entity("Peter");
	entity.PrintName();

	// This will call the move constructor.
	String string = "Hello";
	String apple = "Apple";
	String dest;
	std::cout << "Apple: ";
	apple.Print();
	std::cout << "Dest: ";
	dest.Print();

	// This will call the move assignment operator. This is because when you first define the variable, it needs to be constructed so the move constructor is called. But when you assign it to another variable,since the variable is already constructed and you are simply assigning new data to it, the move assignment operator is called.
	dest = std::move(apple);
	std::cout << "Apple: ";
	apple.Print();
	std::cout << "Dest: ";
	dest.Print();
	// Same thing as '((String&&)string)'.
	// String dest = std::move(string);
	std::cin.get();
}