#include <iostream>
#include <random>

class Singleton
{
private:
    Singleton() {}
    // This deletes the copy constructor.
    Singleton(const Singleton &) = delete;
    static Singleton s_Instance;
    // This deletes the assingment operator.
    Singleton &operator=(const Singleton &) = delete;

public:
    static Singleton &Get() { return s_Instance; }
    void Function() {};
};

class Random
{
private:
    Random() {}
    // This deletes the copy constructor.
    Random(const Random &) = delete;
    static Random r_Instance;
    // I in IFloat stands for Internal, a naming convention.
    float IFloat(float lower, float upper)
    {
        std::random_device rd;                                    // Obtain a random number from hardware
        std::mt19937 gen(rd());                                   // Seed the generator
        std::uniform_real_distribution<float> dist(lower, upper); // Define the distribution

        return dist(gen); // Generate and return the random float
    };

public:
    static Random &Get() { return r_Instance; }
    float Float(float lower = 0.0f, float upper = 1.0f)
    {
        std::random_device rd;                                    // Obtain a random number from hardware
        std::mt19937 gen(rd());                                   // Seed the generator
        std::uniform_real_distribution<float> dist(lower, upper); // Define the distribution

        return dist(gen); // Generate and return the random float
    };
    // This method is used so that we don't have to write 'Random::Get().Float()', instead we can use 'Random::GetFloat()'.
    // You can comment out the Float function and replace this function to Float.
    static float GetFloat(float lower = 0.0f, float upper = 1.0f) { return Get().IFloat(lower, upper); }
};

Random Random::r_Instance;
// This is eager initialization, move this inside the 'Get()' function for lazy initialization.
Singleton Singleton::s_Instance;

int main()
{
    Singleton::Get().Function();

    // If copy constructor is not deleted, code below copies the singleton instance, which defeats the purpose of having a singleton.
    // Singleton instance = Singleton::Get();
    Singleton &instance = Singleton::Get();
    std::cout << Random::Get().Float() << std::endl;
    std::cout << Random::GetFloat(1.0, 2.0) << std::endl;
    std::cin.get();
}