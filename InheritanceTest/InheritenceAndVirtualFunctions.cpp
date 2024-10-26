// #define String std::string

// #include <iostream>
// #include <string>

// class Entity
// {
// public:
//     virtual String GetName() { return "Entity"; }
// };

// class Player : public Entity
// {
// private:
//     String m_Name;

// public:
//     Player(const String &name) : m_Name(name) {}
//     String GetName() override { return m_Name; }
// };

// void PrintName(Entity *entity)
// {
//     std::cout << entity->GetName() << std::endl;
// }

// int main()
// {
//     Entity *e = new Entity();
//     PrintName(e);

//     Player *p = new Player("Merdo");
//     PrintName(p);

//     std::cin.get();
// }