#include <iostream>

// class Singleton
// {
// private:
//     static Singleton *s_Instance;

// public:
//     static Singleton &Get() { return *s_Instance; }
// };

// Singleton *Singleton::s_Instance = nullptr;

class Singleton
{
public:
    static Singleton &Get()
    {
        // If this wasn't declared as static, the instance would be deleted at the end of the scope.
        static Singleton instance;
        return instance;
    }
};

void Function()
{
    static int i = 0;
    i++;
    std::cout << i << std::endl;
}

int main()
{
    Function();
    Function();
    Function();
    Function();
    Function();
    std::cin.get();
}