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

	// The 'explicit' keyword prevents the compiler from using this constructor for implicit conversions. This means that you cannot use an int to create an Entity object without explicitly calling the constructor. This is useful to avoid unintended conversions that can lead to bugs.
    explicit Entity(const int age) : m_Name("Unknown"), m_Age(age) {}
};

void PrintEntity(const Entity &entity)
{
    // Printing
}

int main()
{
    // Without the 'explicit' keyword on the constructor this would work because when you call the 'PrintEntity' function which expects an Entity object it would automaticly convert it to Entity since Entity class has a constructor with int as parameter. But in this case it won't work since explicit keyword is used.
    // PrintEntity(24);

	// This could work because the constructor with String parameter is not marked as explicit. But the compiler would have to do two conversions; one from const char* to String and then from String to Entity. The compiler only allows one implicit conversion at a time, so it will not compile.
    //PrintEntity("Tokat");
    // So the correct version would be something like this:
	PrintEntity(String("Tokat"));
    PrintEntity((Entity)24);

    Entity a = String("Entity A");
    Entity b = "Tokat";

    // This would also work normally due to the reason explained above but in this case it won't because the explicit keyword is used.
    // Entity c = 22;
    Entity c(22);
    std::cin.get();
}