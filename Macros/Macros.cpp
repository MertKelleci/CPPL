#include <iostream>

// You can define your own macros for different configurations, such as debug and release modes. To do that, you can go to Project Properties -> C/C++ -> Preprocessor -> Preprocessor Definitions and add your own definitions, such as DEBUG or RELEASE. Then, you can use conditional compilation to include or exclude code based on these definitions. For example:
#ifdef DEBUG
#define LOG(x) std::cout << x << std::endl
#else
#define LOG(x) // Do nothing
#endif

// This way you can have different behavior in debug and release modes without changing your code. In debug mode, the LOG macro will print the message to the console, while in release mode, it will do nothing.

#define MAIN                 \
    int main()               \
    {                        \
        LOG("Hello World!"); \
        std::cin.get();      \
    }

MAIN