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
    // This is creates the object on the stack, which is deleted at the end of the scope
    Entity stack_entity("Stack Entity");

    Entity *e_0, *e_1;
    // This is an empty bracket. Doesn't do anything, but objects instantaited in the stack still get destroyed at the end.
    {
        // Created on stack.
        Entity entity_stack = Entity("Entity Stack");
        e_0 = &entity_stack;
        // Created on heap. Have to be manually terminated, takes more memory than one which is created on stack.
        Entity *entity_heap = new Entity("Entity Heap");
        e_1 = entity_heap;
        std::cout << e_0->GetName() << std::endl;
    }
    std::cout << e_1->GetName() << std::endl;

    // This still works but it's called a dangling pointer, and is undefined behavior. The method still works because that piece of memory hasn't been reused yet.
    // std::cout << e_0->GetName() << std::endl;
    std::cin.get();
    delete e_1;
}