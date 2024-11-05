#include <iostream>

int main()
{
    // Both of these allocates 200 bytes of memory. **a2d just allocates pointers, which are also just integers.
    // When you assign something to a2d, you are just assinging integer pointers which point to corresponding arrays.
    // int *array = new int[50];

    // int **a2d = new int *[50];
    // for (int i = 0; i < 50; i++)
    //     a2d[i] = new int[50];

    // These arrays are unlikely to be close to one another. So you have to constantly jump around and fetch these arrays, making the code performance wise bad.
    int ***a3d = new int **[5];
    for (int i = 0; i < 5; i++)
    {
        a3d[i] = new int *[5];
        for (int j = 0; j < 5; j++)
            a3d[i][j] = new int[5];
    }

    for (int i = 0; i < 5; i++)
    {
        for (int j = 0; j < 5; j++)
        {
            delete[] a3d[i][j]; // Delete the innermost array
        }
        delete[] a3d[i]; // Delete the second-level array
    }
    delete[] a3d; // Delete the outermost array

    // Instead of multidimentional arrays, you can/should use one dimentional array.
    // Since this is just one array, the stored values are contiguous, therefore easier to access since it doesn't require jumping much from memory to memory.
    int *array = new int[5 * 5];
    for (int y = 0; y < 5; y++)
        for (int x = 0; x < 5; x++)
            array[x + y * 5] = 2;

    delete[] array;

    std::cin.get();
}