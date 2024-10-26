#include <iostream>
#include <string>

class Example
{
public:
    Example()
    {
        std::cout << "Created Example" << std::endl;
    }

    Example(int x)
    {
        std::cout << "Created Example with" << x << std::endl;
    }
};

class Entity
{
private:
    std::string m_Name;
    Example m_Example;

public:
    //  Entity(){m_Name = "Unknown";}
    // When initialized like this, make sure it's initialized in the order which the class members are defined in
    // Entity() : m_Name("Unknown") {}

    // Entity(const std::string &name) { m_Name = name; }
    Entity(const std::string &name) : m_Name(name) {};

    // When initialized like this, the Example class is created twice, one of the is wasted, which leads to poor performance
    // The primitive data types are exempt from this, but still good practice to initialize them in Constructor Initializer List also
    Entity()
    {
        m_Name = "Unknown";
        m_Example = Example(8);
    }

    // This is the correct way to intitialize
    // Entity(): m_Name("Unknown"), m_Example(Example(8)){};
    // Entity(): m_Name("Unknown"), m_Example(8){};

    const std::string &GetName() const { return m_Name; }
};

int main()
{
    Entity e0, e1("Merdo");
    std::cout << e0.GetName() << std::endl;
    std::cout << e1.GetName() << std::endl;
    std::cin.get();
}