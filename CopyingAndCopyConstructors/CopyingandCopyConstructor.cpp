#include <iostream>

struct Vector2
{
    float x, y;
};

std::ostream &operator<<(std::ostream &stream, const Vector2 &vector2)
{
    stream << "(" << vector2.x << ", " << vector2.y << ")";
    return stream;
}

int main()
{
    Vector2 a = {2, 3};
    Vector2 b = a;
    b.x = 5;

    Vector2 *a_ptr = new Vector2();
    Vector2 *b_ptr = a_ptr;

    a_ptr->y = 7;
    a_ptr->x = 7;

    b_ptr->y = 6;
    b_ptr->x = 6;

    std::cout << a << " " << b << std::endl;
    std::cout << (*a_ptr) << " " << (*b_ptr) << std::endl;
    std::cin.get();
}