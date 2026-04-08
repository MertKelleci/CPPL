#include <algorithm>
#include <chrono>
#include <cmath>
#include <fstream>
#include <iostream>
#include <string>

#include <thread>

//Tracing tool preinstalled on Chromium based browsers is a powerful tool for visual benchmarking of web applications. It allows developers to record and analyze the performance of their applications in great detail. You can access it by going to 'chrome://tracing'.

namespace Benchmark
{
	struct ProfileResult
	{
		std::string Name;
		long long Start, End;
		uint32_t ThreadID;
	};

	struct InstrumentationSession
	{
		std::string Name;
	};

	class Instrumentor
	{
	private:
		InstrumentationSession* m_CurrentSession;
		std::ofstream m_OutputStream;
		int m_ProfileCount;

	public:
		Instrumentor()
			: m_CurrentSession(nullptr), m_ProfileCount(0)
		{}

		// This code simply creates the "results.json" file which will be used for creating visual benchmarking and writes the header to it. It also initializes the current session with the provided name.
		void BeginSession(const std::string& name, const std::string& filepath = "results.json")
		{
			m_OutputStream.open(filepath);
			WriteHeader();
			m_CurrentSession = new InstrumentationSession{ name };
		}


		// This code simply ends the current session by writing the footer to the "results.json" file, closing the output stream, and cleaning up the current session and profile count.
		void EndSession()
		{
			WriteFooter();
			m_OutputStream.close();
			delete m_CurrentSession;
			m_CurrentSession = nullptr;
			m_ProfileCount = 0;
		}

		void WriteProfile(const ProfileResult& result)
		{
			if (m_ProfileCount++ > 0)
				m_OutputStream << ",";

			std::string name = result.Name;
			std::replace(name.begin(), name.end(), '"', '\'');

			m_OutputStream << "{";
			m_OutputStream << "\"cat\":\"function\",";
			m_OutputStream << "\"dur\":" << (result.End - result.Start) << ',';
			m_OutputStream << "\"name\":\"" << name << "\",";
			m_OutputStream << "\"ph\":\"X\",";
			m_OutputStream << "\"pid\":0,";
			m_OutputStream << "\"tid\":" << result.ThreadID << ",";
			m_OutputStream << "\"ts\":" << result.Start;
			m_OutputStream << "}";

			m_OutputStream.flush();
		}

		void WriteHeader()
		{
			m_OutputStream << "{\"otherData\": {},\"traceEvents\":[";
			m_OutputStream.flush();
		}

		void WriteFooter()
		{
			m_OutputStream << "]}";
			m_OutputStream.flush();
		}

		static Instrumentor& Get()
		{
			static Instrumentor instance;
			return instance;
		}
	};
}

#define PROFILING 1
#if PROFILING
// This is a preprocessor token-paste that creates a unique local variable name for the timer object. •	## concatenates tokens. timer##__LINE__ becomes something like timer100 if the macro is expanded on line 100 (because __LINE__ is the current line number). The macro expands to a declaration of an InstrumentationTimer instance, e.g.: InstrumentationTimer timer100("some name");.
#define PROFILE_SCOPE(name) InstrumentationTimer timer##__LINE__(name)
// If you have more than one function with the same name, __FUNCTION__ macro will not be sufficient to differentiate them. In that case, you can use __FUNCSIG__ macro instead, which provides the full function signature, including the class name and parameter types. This can help you distinguish between different functions with the same name in your profiling results.
#define PROFILE_FUNCTON() PROFILE_SCOPE(__FUNCTION__)
#else
#define PROFILE_SCOPE(name)
#endif

// This is a simple timer class that starts timing when it is created and stops timing when it is destroyed. It uses the high-resolution clock to measure the time taken for a specific scope of code. When the timer is stopped, it calculates the duration and writes the profile result to the Instrumentor.
class InstrumentationTimer
{
public:
	InstrumentationTimer(const char* name) : m_Name(name)
	{
		m_StartTimepoint = std::chrono::high_resolution_clock::now();
	}

	~InstrumentationTimer() { Stop(); }

private:
	std::chrono::time_point<std::chrono::high_resolution_clock> m_StartTimepoint;
	const char* m_Name;

	void Stop()
	{
		auto endTimepoint = std::chrono::high_resolution_clock::now();
		auto start = std::chrono::time_point_cast<std::chrono::microseconds>(m_StartTimepoint).time_since_epoch().count();
		auto end = std::chrono::time_point_cast<std::chrono::microseconds>(endTimepoint).time_since_epoch().count();

		// This code calculates the thread ID by hashing the current thread's ID using std::hash. The resulting thread ID is a unique identifier for the thread that can be used in the profiling results to differentiate between different threads. We used hash function here because std::thread::id does not have a built-in way to convert it to a numeric value, and hashing provides a way to generate a unique numeric representation of the thread ID.
		uint32_t threadID = std::hash<std::thread::id>{}(std::this_thread::get_id());
		auto duration = end - start;
		double ms = duration * 0.001;

		Benchmark::Instrumentor::Get().WriteProfile({ m_Name, start, end, threadID });
	}
};

void Function1()
{
	PROFILE_FUNCTON();
	for (int i = 0; i < 1000; i++)
		std::cout << "Hello World #" << sqrt(i) << std::endl;
}
void Function2()
{
	PROFILE_FUNCTON();
	for (int i = 0; i < 1000; i++)
		std::cout << "Hello World #" << i << std::endl;
}

void RunBenchmarks()
{
	PROFILE_FUNCTON();
	std::cout << "Running Benchmarks...\n";
	std::thread a([]()
		{
			Function1();
		});
	std::thread b([]()
		{
			Function2();
		});

	a.join();
	b.join();
}

int main()
{
	Benchmark::Instrumentor::Get().BeginSession("Profile");
	RunBenchmarks();
	Benchmark::Instrumentor::Get().EndSession();
	std::cin.get();
}