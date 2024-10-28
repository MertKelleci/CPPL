#include <iostream>
#include <string>

class Entity
{
public:
    Entity() { std::cout << "Created Entity" << std::endl; }
    ~Entity() { std::cout << "Destroyed Entity" << std::endl; }
};

int *CreateArray()
{
    // Once this function is done, the array, which is created in the stack, will be deleted.
    // int array[50];

    int *array = new int[50];
    return array;
}

class ScopedPtr
{
private:
    Entity *m_Ptr;

public:
    ScopedPtr(Entity *ptr) : m_Ptr(ptr) {}
    ~ScopedPtr() { delete m_Ptr; }
};

int main()
{
    {
        Entity e;

        // This creates a scoped pointer.
        ScopedPtr e_scp = new Entity();
    }

    std::cin.get();
}