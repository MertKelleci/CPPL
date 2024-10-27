#include <iostream>
#include <string>

using String = std::string;

class Entity
{
private:
    String m_Name;

public:
    Entity() : m_Name("Unknown") {}
    Entity(const String &name) : m_Name(name) {}

    const String &GetName() const { return m_Name; }
};

int main()
{
    int *b = new int[10];
    Entity *e = new Entity();
    // Same thing as down below, but also calls the constructor.
    // new(x) -> creates the memory at x memory address.
    // Entity *e = (Entity *)malloc(sizeof(Entity));

    delete e;
    // Same thing as free(e) like in C, but also calls the destructor.

    delete[] b;
    std::cin.get();
}