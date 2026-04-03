#define String std::string

#include <iostream>
#include <string>

class Printable
{
public:
	// In C++, a pure virtual function is a virtual function that has no implementation in the base class and must be overridden in any derived class. It is declared by assigning 0 to the function declaration in the base class. A class that contains at least one pure virtual function is called an abstract class, and it cannot be instantiated directly. Derived classes must provide an implementation for all pure virtual functions to be instantiable.
	virtual String GetClassName() = 0;
};

class Entity : public Printable
{
public:
	// virtual String GetName() = 0;
	String GetClassName() override { return "Entity"; }
};

class Player : public Entity
{
private:
	String m_Name;

public:
	Player(const String& name) : m_Name(name) {}
	//String GetName() override { return m_Name; }
	String GetClassName() override { return m_Name; }
};

//void PrintName(Entity *entity)
//{
//    std::cout << entity->GetName() << std::endl;
//}

void Print(Printable* obj)
{
	std::cout << obj->GetClassName() << std::endl;
}

int main()
{
	Entity* e = new Entity();
	// Entity *e = new Player("Cherno");
	// PrintName(e);

	Player* p = new Player("Merdo");
	// PrintName(p);

	Print(e);
	Print(p);

	std::cin.get();
}