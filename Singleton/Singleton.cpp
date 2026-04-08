#include <iostream>
#include <random>

// Unlike in Java or C#, C++ does not have built-in support for singletons, so we have to implement it ourselves. The main idea is to make the constructor private and provide a static method that returns a reference to the single instance of the class. We also delete the copy constructor and assignment operator to prevent copying of the singleton instance. And since also unlike in Java or C#, C++ is not a strictly object-oriented language, so basically we can achieve the things you would normaly need a singleton for, with just a namespace and free functions.
class Singleton
{
private:
	Singleton() {}

	// This deletes the copy constructor. By doing so, you prevent the singleton instance from being copied, and if you had non-static variables inside this singleton class, those would be physically copied. So deleting the copy constructor prevents code such as this:
	// Singleton copy = Singleton::Get();
	Singleton(const Singleton&) = delete;

	// This is a declaration, not a definiton. You must provide one definition (and thus allocate storage and run its constructor) in a single translation unit, otherwise the linker will give an "undefined reference" error.
	static Singleton s_Instance;
	// This deletes the assingment operator.
	Singleton& operator=(const Singleton&) = delete;

public:

	// For lazy, thread-safe initialization, you can define the static instance as a local static variable inside the 'Get()' function. This is because if it is inside a static function, the compiler will create memory space for it.
	static Singleton& Get() { return s_Instance; }
	void Function() {};
};

class Random
{
private:
	Random() {}
	// This deletes the copy constructor.
	Random(const Random&) = delete;

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
	static Random& Get() { return r_Instance; }

	// This is a copy of the IFloat function and it's just here for learning purposes.
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

// This is eager initialization, move this inside the 'Get()' function for lazy initialization. Static  data member declared inside a class is only a declaration, not storage. You must provide one definition (and thus allocate storage and run its constructor) in a single translation unit, otherwise the linker will give an "undefined reference" error. Since C++17, you can make it inline in-class so no out-of-class definition is needed: "inline static Singleton s_Instance;". Additionally, if you want to use lazy initialization, you can define the static instance as a local static variable inside the 'Get()' function. This way, the instance will only be created when 'Get()' is called for the first time, and it will be destroyed automatically when the program ends: static Singleton& Get() { static Singleton instance; return instance; }.
Singleton Singleton::s_Instance;

int main()
{
	Singleton::Get().Function();

	// If copy constructor is not deleted, code below copies the singleton instance, which defeats the purpose of having a singleton.
	// Singleton instance = Singleton::Get();
	Singleton& instance = Singleton::Get();
	std::cout << Random::Get().Float() << std::endl;
	std::cout << Random::GetFloat(1.0, 2.0) << std::endl;
	std::cin.get();
}