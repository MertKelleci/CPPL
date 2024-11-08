#include <iostream>
#include <string>
#include <fstream>
#include <optional>

std::optional<std::string> ReadFileAsString(const std::string &filepath)
{
    std::ifstream stream(filepath);
    if (stream)
    {
        std::string result;
        stream.close();
        return result;
    }

    return {};
}

int main()
{
    std::optional<std::string> data = ReadFileAsString("data.txt");
    if (data.has_value())
    {
        std::cout << "File read succesfully\n";
        std::string &string = *data;
        std::cout << data.value();
    }
    else
    {
        std::cout << "File could not be opened\n";
    }

    std::cin.get();
}