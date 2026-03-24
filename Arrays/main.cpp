#include <iostream>

class Entity
{
public:
    //Since declaring an array in this way creates it in the stack, the array itself will be embeded inside the memory block assigned for this Entity object.
    //int example[5];

	//Since declaring an array in this way creates it in the heap, the array will be allocated separately from the Entity object, and the pointer to the array will be stored inside the Entity object. This allows for more flexible memory management, but it also means that we need to manually manage the memory for the array, including deleting it when we're done using it to avoid memory leaks.
    //This is whats called memory fragmentation.
	int* example = new int[5];

    Entity()
    {
        int a[5];
		int* b = new int[5];

		//Passing an array created in the stack to the 'sizeof' function will give us the total size of the array in bytes, which is 20 bytes for an array of 5 integers (assuming each integer is 4 bytes). However, passing a pointer to an array created in the heap to the 'sizeof' function will give us the size of the pointer itself, which is typically 8 bytes on a 64-bit system, regardless of the size of the array it points to. This is because 'sizeof' only knows about the size of the pointer, not the size of the memory it points to.
		int count = sizeof(a) / sizeof(int);
		int count2 = sizeof(b) / sizeof(int);

        for (int i = 0; i < 5; i++)
            example[i] = 2;
	}
};

int main()
{
    // This array's lifetime ends when we hit the endbracket since it's created in stack.
    int example[5];
    for (int i = 0; i < 5; i++)
        example[i] = 5 - i;

	//Since arrays are contiguous blocks of memory and simply an int pointer, we can use pointer arithmetic to access and modify their elements.
    int* ptr = example;
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

	// This array is created on heap so it must be deleted manually. While this approach gives us more control over the lifetime of the array, it can also cause problems such as memory leaks if we forget to delete the array when we're done using it or memory fragmentation if we create and delete many arrays of different sizes over time.
    //Furhter detail on memory fragmentation is on Entity class.
    int* another = new int[5];
    delete[] another;
    std::cin.get();
}