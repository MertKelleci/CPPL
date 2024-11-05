#include <iostream>
#include <vector>
#include <algorithm>
#include <functional>

int main()
{
    std::vector<int> values = {1, 5, 2, 4, 3};

    // This 'sort' function comes from <functional>, and 'greater' function comes from <algorithm>
    // If function parameter is left blank, it will automatically sorted from smallest number to biggest number.
    std::sort(values.begin(), values.end(), std::greater<int>());
    for (int value : values)
        std::cout << value << " ";
    std::cout << std::endl;

    // When lambda funtion returns true the first argument comes first, and vice versa.
    std::sort(values.begin(), values.end(), [](int a, int b)
              { 
                if(a==1)
                    return false;
                if(b==1)
                    return true;
                return a < b; });

    for (int value : values)
        std::cout << value << " ";
    std::cout << std::endl;
    std::cin.get();
}
