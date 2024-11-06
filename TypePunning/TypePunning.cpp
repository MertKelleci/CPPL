#include <iostream>

struct Entity
{
    int x, y;

    int *GetPoisitions()
    {
        return &x;
    }
};

int main()
{
    // When you print this double value, you won't get 50 because even though 50 is stored in the first 4 bytes of memory, the other 4 bytes which come from double are random.
    // int a = 50;
    // double value = *(double *)&a;
    // std::cout << value << std::endl;

    Entity e = {5, 8};
    int *position = (int *)&e;
    std::cout << position[0] << ", " << position[1] << std::endl;

    // The reason we've added +4 is because a char is 1 byte and an int is 4.
    // Since we need the second integer value, which is 4 bytes ahead, we need to move 4 char worth of bytes ahead.
    // What type punning basically is, we get the address of a value, cast it's pointer to something else, then dereference it if you have to.
    int y = *(int *)((char *)&e + 4);
    std::cout << "e.y value: " << y << std::endl;

    int *positions = e.GetPoisitions();
    std::cout << positions[1] << std::endl;
    std::cin.get();
}