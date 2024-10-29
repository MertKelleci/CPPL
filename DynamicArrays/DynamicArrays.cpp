#include <iostream>
#include <string>
#include <vector>

struct Vertex
{
    float x, y, z;
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
    vertices.push_back({1, 2, 3});
    vertices.push_back({4, 5, 6});

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