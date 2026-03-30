#include <iostream>
#include <string.h>

struct Vector2
{
    float x, y;
};

class String
{
private:
    char *m_Buffer;
    unsigned int m_Size;

public:
    String(const char *string)
    {
        m_Size = strlen(string);
        m_Buffer = new char[m_Size + 1];
        memcpy(m_Buffer, string, m_Size);
        m_Buffer[m_Size] = 0;
    }

    // This is a copy constructor. Enables you to create a deep copy. How it works under the hood:
    // String(const String &other)
    // {
    //     memcpy(this, &other, sizeof(String));
    // }
     
    
    // String(const String &other) = delete; makes it like an unique pointer, removes the ability to copy.
    
	// This is a copy constructor. It creates a new String object by copying the contents of another String object. It allocates new memory for the buffer and copies the string data, ensuring that each String object manages its own memory. You can create a copy constructor by defining a constructor that takes a reference to an object of the same class as a parameter. The copy constructor is called when you create a new object as a copy of an existing object, such as when you pass an object by value or return an object from a function.
    String(const String &other) : m_Size(other.m_Size)
    {
        std::cout << "Coppied String" << std::endl;
        m_Buffer = new char[m_Size + 1];
        memcpy(m_Buffer, other.m_Buffer, m_Size + 1);
    }

	// This is an overloaded operator. It allows you to use the [] operator on String objects. It returns a reference to the character at the specified index, which allows you to modify the character directly.
    char &operator[](unsigned int index)
    {
        return m_Buffer[index];
    }

    ~String() { delete[] m_Buffer; }

	// Since this method is declared as friend, you can use string's properties in the definiton of the function.
    friend std::ostream &operator<<(std::ostream &stream, const String &string);
};

std::ostream &operator<<(std::ostream &stream, const String &string)
{
    // Since this function is declared as friend in String class, you can use string's properties.
    stream << string.m_Buffer;
    return stream;
}

std::ostream &operator<<(std::ostream &stream, const Vector2 &vector2)
{
    stream << "(" << vector2.x << ", " << vector2.y << ")";
    return stream;
}

// If this method's signature wasn't a reference, it would copy the string.
void PrintString(const String &str)
{
    std::cout << str << std::endl;
}

int main()
{

	// With the exception of references, when you assign a value to another, you are always copying. With classes, you can control how the copying is done by implementing a copy constructor. If you don't implement a copy constructor, the compiler will create a default one for you, which performs a shallow copy. A shallow copy copies all the member values, but if those members are pointers, it only copies the pointer value, not the data it points to. This can lead to issues like double deletion if both objects try to delete the same memory in their destructors.
    Vector2 a = {2, 3};
    Vector2 b = a;
    b.x = 5;

    Vector2 *a_ptr = new Vector2();
    Vector2 *b_ptr = a_ptr;

    a_ptr->y = 7;
    a_ptr->x = 7;

    b_ptr->y = 6;
    b_ptr->x = 6;

    std::cout << a << " " << b << std::endl;
    std::cout << (*a_ptr) << " " << (*b_ptr) << std::endl;

    // If the following code is executed without implementing deep copy, the original string will change and you'll get a crash after the program terminates.
    // That's because a shallow copy only copies the pointer value when creating a copy. And since the m_Buffer variable is a pointer, the compiler will copy the pointer and both the original String and its copy will be pointing to the same adress. So when you terminate the program, the compiler will try to delete the same string twice in deconstructor, thus create an error.
    String string = "Mrt";
    String second = string;

    // Overloaded operator here.
    second[2] = 'e';

    std::cout << string << std::endl;
    std::cout << second << std::endl;
    std::cout << "=================================" << std::endl;

    PrintString(string);
    PrintString(second);
    std::cin.get();
}