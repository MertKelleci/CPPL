#include <iostream>

int main()
{
    // This array's lifetime ends when we hit the endbracket since it's created in stack.
    int example[5];
    for (int i = 0; i < 5; i++)
        example[i] = 5 - i;

	//Since arrays are contiguous blocks of memory and simply an int pointer, we can use pointer arithmetic to access and modify their elements.
    int *ptr = example;
    example[1] = 5;

	//Since ptr is an int pointer, adding 2 to it will move the pointer to the next integer in the array, which is example[2]. So, *(ptr + 2) is equivalent to example[2].
	//The reason why '+2' works in this case is because the pointer arithmetic takes into account the size of the data type. When you add 2 to an int pointer, it moves the pointer by 2 times the size of an int (which is typically 4 bytes). So, it effectively moves to the next integer in the array.
    *(ptr + 2) = 6;
    
	//Here in this case, we are casting the pointer to a char pointer, which allows us to access the memory byte by byte. By adding 12 to the char pointer, we are moving 12 bytes forward in memory, which corresponds to the location of example[3] (since each int is typically 4 bytes). So, *(int *)((char *)ptr + 12) is equivalent to example[3].
    //What happens step by step:
	//1. We cast the int pointer 'ptr' to a char pointer, which allows us to access the memory byte by byte.
	//2. We add 12 to the char pointer, which moves the pointer 12 bytes forward in memory.Since each int is typically 4 bytes, this corresponds to moving to the location of example[3].
	//3. We then cast the resulting char pointer back to an int pointer, allowing us to access the integer value at that location.
	//4. Finally, we derefference the int pointer to assign the value 7 to example[3].
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