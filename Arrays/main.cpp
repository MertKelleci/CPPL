#include <iostream>

int main()
{
    // This array's lifetime ends when we hit the endbracket since it's created in stack.
    int example[5];
    for (int i = 0; i < 5; i++)
        example[i] = 5 - i;

    int *ptr = example;
    example[1] = 5;
    *(ptr + 2) = 6;

    *(int *)((char *)ptr + 12) = 7;

    for (int i = 0; i < 5; i++)
    {
        std::cout << example[i] << " ";
    }
    std::cout << std::endl;

    // This array is created on heap so it must be deleted manually.
    int *another = new int[5];
    delete[] another;
    std::cin.get();
}