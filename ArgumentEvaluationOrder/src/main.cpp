#include <iostream>

void foo(int a, int b)
{
	std::cout << a << " + " << b << " = " << a + b << std::endl;
}

int main()
{
	int x = 0;

	// The order of evaluation of function arguments is unspecified in C++, so this is undefined behaviour. You'll get different results on different compilers or even different runs of the same program. In general, you should avoid writing code that relies on the order of evaluation of function arguments, as it can lead to unpredictable behavior.

	// When you run this program on debug mode, you get the following printed to the console: 1 + 0 = 1
	// When you run this program on release mode, you get the following printed to the console: 1 + 0 = 1
	foo(x++, x++);

	// When you run this program on debug mode, you get the following printed to the console: 4 + 3 = 7
	// When you run this program on debug mode, you get the following printed to the console: 4 + 3 = 7
	foo(++x, ++x);
	std::cin.get();
}