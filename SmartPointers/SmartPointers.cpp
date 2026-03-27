#include <iostream>
#include <string>
#include <memory>

class Entity
{
public:
    Entity() { std::cout << "Created Entity" << std::endl; }
    ~Entity() { std::cout << "Destroyed Entity" << std::endl; }
};

int main()
{
    {
        std::shared_ptr<Entity> e0;
        {
            //  First smart pointer: Unique pointer. Has lower overhead but it is a scoped pointer, meaning when you are out of scope, it is deleted.
            std::unique_ptr<Entity> unique_entity = std::make_unique<Entity>();
			// This won't work since it's an unique ptr and unique ptr can't be coppied, only moved. This is because if you delete the unique pointer, the memory will be freed and the other pointer will be dangling.
            // std::unique_ptr<Entity> e0 = unique_entity;

            //  Second smart pointer: Shared pointer. Uses reference counting. Increases the ref counter when coppied, decreases at the end of scope. When reference counter reaches 0, the memory is freed.
            std::shared_ptr<Entity> shared_entity = std::make_shared<Entity>();

			// The code below is perfectly fine but I commented it and created a shared_ptr out of scope to demonstrate that it doesn't get deleted at the end of scope, since the ref counter is increased.
            // std::shared_ptr<Entity> e0 = shared_entity;
            e0 = shared_entity;

            // Third smart pointer: Weak pointer. Like shared pointer, but ref count doesn't inrease.
            std::weak_ptr<Entity> weak_entity = shared_entity;
        }
    }
    std::cin.get();
}