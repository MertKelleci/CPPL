#include <iostream>
#define LOG(x) std::cout << x << std::endl

#define MAIN                 \
    int main()               \
    {                        \
        LOG("Hello World!"); \
        std::cin.get();      \
    }

MAIN