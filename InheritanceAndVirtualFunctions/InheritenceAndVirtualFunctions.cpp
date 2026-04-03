#define string std::string

#include <iostream>
#include <string>

class entity
{
public:
	// In C++, virtual functions are used to achieve runtime polymorphism. When a function is declared as virtual in a base class, it can be overridden in derived classes. This allows the program to determine at runtime which function to call based on the type of the object being pointed to, rather than the type of the pointer itself. A child class has to override the virtual function to provide its own implementation. If it does not, the base class's implementation will be used when the function is called through a pointer or reference to the base class.
	virtual string getname() { return "entity"; }
};

class player : public entity
{
private:
	string m_name;

public:
	player(const string& name) : m_name(name) {}
	string getname() override { return m_name; }
};

void printname(entity* entity)
{
	std::cout << entity->getname() << std::endl;
}

int main()
{
	entity* e = new entity();
	printname(e);

	player* p = new player("merdo");
	printname(p);

	std::cin.get();
}