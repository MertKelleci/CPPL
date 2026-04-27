#include <iostream>

class Entity
{
public:
	Entity() = default;

	const std::string& GetName() const { return m_Name; }
	void PrintType()
	{
		std::cout << "Entity" << std::endl;
	}

private:
	Entity* m_Parent;
	std::string m_Name;
};


// The following is what C++ compiler translates the code above into. It is not exactly the same as the code above, but it gives you an idea of what is going on under the hood.
struct EntityData
{
	// Since this is the very first member variable, it will be at offset 0, and the next member variable will be at offset 8 (assuming a 64-bit system) because this is a pointer and pointers are (depending on your compiler) 8 bytes in size.
	EntityData* m_Parent;
	std::string m_Name;
};

// While this function takes an EntityData pointer, it does not access any member variables of the EntityData struct, so it will not cause a crash even if we pass a null pointer to it. This is the reason why we can call e->PrintType() without causing a crash, even though e is a null pointer.
void Entity_PrintType(const EntityData* self)
{
	std::cout << "EntityData" << std::endl;
}

// This function will obviously cause a crash if we try to call it with a null pointer, because it tries to access the m_Name member variable of the EntityData struct.
const std::string& Entity_GetName(const EntityData* self)
{
	return self->m_Name;
}

// If we were to have a function that is static, it wouldn't have EntityData* self as a parameter. That is why when we create a static member function in the Entity class, we can not access any variable not marked as static, because it doesn't have its self as a member therefore doesn't know what our non-static variables are.

int main()
{
	Entity* e = nullptr;

	// This will cause a crash because we are trying to dereference a null pointer.
	// std::cout << e->GetName() << std::endl;

	// This code will work fine because we are not dereferencing the pointer, we are just calling a member function that does not access any member variables.
	e->PrintType();


	uint64_t offset = offsetof(EntityData, m_Name);
	std::cout << "Offset of m_Name: " << offset << std::endl;

	// This is pretty much what the offsetof macro does under the hood. It calculates the offset of a member variable by taking the address of that member variable in a null pointer to the struct. Since we are not actually dereferencing the pointer, this is safe to do and will not cause a crash.
	offset = (uint64_t) & ((EntityData*)nullptr)->m_Name;
	std::cout << "Offset of m_Name (manual calculation): " << offset << std::endl;
	std::cin.get();
}

