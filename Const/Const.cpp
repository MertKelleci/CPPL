#include <iostream>
#include <string>

class Entity
{
private:
    int m_X;
    std::string m_Name;
    int *m_Y;
    mutable int var;

public:
    int GetX() const
    {
        // Since var variable is declared mutable, it can be changed inside a const function
        var = 2;
        return m_X;
    }

    const int *const GetY() const
    {
        return m_Y;
    }

    const std::string &GetName() const { return m_Name; }
};

// Since Entity is declaraed const you can't call any method that isn't declared const because what if the function were to make changes to the object
void PrintEntity(const Entity &e)
{
    std::cout << e.GetX() << std::endl;
}

int main()
{
    const int MAX_AGE = 90;
    // const int* a = new int == int const* a =new int;;
    // *a = 2; -> won't work
    // a = (int*)&MAX_AGE;

    // int* const a = new int;
    // *a = 2;
    // a = (int*)&MAX_AGE; -> won't work

    // const int* const a = new int;
    // *a = 2 -> won't work;
    // a = (int*)&MAX_AGE; -> won't work

    Entity e;

    int x = 8;
    // f = [&x] can be used also, no need to declare mutable in that case
    auto f = [=]() mutable
    {
        x++;
        std::cout << x << std::endl;
    };

    f();
    // x = 8
    std::cin.get();
}