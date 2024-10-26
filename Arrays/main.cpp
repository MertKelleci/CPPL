#include <iostream>

int main()
{
    // Bu stack'te oluşturulduğu için lifetime'ı farklı. End bracket'de silinir.
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

    // Bu heap'te oluşuturulur. End bracket'de silinmez, manuel olarak silinmeli;
    int *another = new int[5];
    delete[] another;
    std::cin.get();
}