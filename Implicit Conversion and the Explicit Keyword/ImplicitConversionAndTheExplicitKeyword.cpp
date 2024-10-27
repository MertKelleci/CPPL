#include <iostream>
#include <string>
using String = std::string;

class Entity
{
private:
    String m_Name;
    int m_Age;

public:
    Entity(const String &name) : m_Name(name), m_Age(-1) {}
    explicit Entity(const int age) : m_Name("Unknown"), m_Age(age) {}
};

void PrintEntity(const Entity &entity)
{
    // Printing
}

int main()
{
    // Won't work since explicit keyword is used.
    // PrintEntity(24);
    PrintEntity((Entity)24);

    Entity a = String("Entity A");

    // Won't work since explicit keyword is used.
    // Entity b = 22;
    Entity b(22);
    std::cin.get();
}