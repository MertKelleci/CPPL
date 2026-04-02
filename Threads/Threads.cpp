#include <chrono>
#include <iostream>
#include <thread>

static bool s_Finished = false;
void DoWork()
{
	using namespace std::literals::chrono_literals;
	while (!s_Finished)
	{
		std::cout << "Working...\n";
		std::this_thread::sleep_for(1s);
	}
}

int main()
{
	// We are sending the function pointer to the thread constructor, so it will call that function in the new thread.
	std::thread worker(DoWork);

	std::cin.get();
	s_Finished = true;

	// The join() function will block the main thread until the worker thread finishes. This is important to ensure that the worker thread has completed its work before the program exits.
	worker.join();
	std::cout << "Finished\n";

	std::cin.get();
}