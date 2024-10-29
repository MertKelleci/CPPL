#include <iostream>
#include <string>
#include <vector>

struct Vertex
{
    float x, y, z;

    Vertex(float x, float y, float z) : x(x), y(y), z(z) {}

    Vertex(const Vertex &vertex) : x(vertex.x), y(vertex.y), z(vertex.z)
    {
        std::cout << "Vertex Copied!" << std::endl;
    }
};

std::ostream &operator<<(std::ostream &stream, Vertex &vertex)
{
    stream << "(" << vertex.x << ", " << vertex.y << ", " << vertex.z << ")";
    return stream;
}

// Without the &, the entire list is coppied.
void Funtion(const std::vector<Vertex> &vertices)
{
}

int main()
{
    std::vector<Vertex> vertices;

    // The reason why we are getting a bunch of copy messages is because the Vertex objects are created in the current stack frame.
    // In this case it's main function. Then the created Vertex objects are sent to actual vector.
    // vertices.push_back({1, 2, 3});
    // vertices.push_back({4, 5, 6});
    // vertices.push_back({7, 8, 9});

    // emplace_back function makes it so that the Vertex objects are created inplace in Vector.
    vertices.reserve(3);
    vertices.emplace_back(1, 2, 3);
    vertices.emplace_back(3, 4, 5);
    vertices.emplace_back(6, 7, 8);

    for (int i = 0; i < vertices.size(); i++)
        std::cout << vertices[i] << std::endl;

    // Without the & sign, each iterated Vertex object is coppied.
    for (Vertex &v : vertices)
        std::cout << v << std::endl;

    // This deletes the 2nd element.
    vertices.erase(vertices.begin() + 1);

    vertices.clear();
    std::cin.get();
}