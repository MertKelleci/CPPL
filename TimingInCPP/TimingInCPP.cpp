#include <iostream>
#include <thread>
#include <chrono>

struct Timer
{
    std::chrono::time_point<std::chrono::_V2::system_clock> start, end;
    std::chrono::duration<float> duration;

    Timer() { start = std::chrono::high_resolution_clock::now(); }
    ~Timer()
    {
        end = std::chrono::high_resolution_clock::now();
        duration = end - start;
        float ms = duration.count() * 1000.0f;
        std::cout << "Timer took: " << ms << "ms..." << std::endl;
    }
};

void Function()
{
    Timer timer;
    for (int i = 0; i < 50; i++)
    {
        std::cout << "Hello World!...\n";
    }
}

int main()
{
    using namespace std::literals::chrono_literals;
    auto start = std::chrono::high_resolution_clock::now();
    std::this_thread::sleep_for(1s);
    auto end = std::chrono::high_resolution_clock::now();

    std::chrono::duration<float> duration = end - start;
    std::cout << duration.count() << "s" << std::endl;
    Function();
    std::cin.get();
}