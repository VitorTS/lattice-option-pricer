#include <iostream>
#include <chrono>

template<class duration_unit = std::chrono::milliseconds>
class Benchmark{
private:
	std::chrono::system_clock clock;
	std::chrono::time_point<std::chrono::system_clock> t0, t1;
	bool started;
public:
	Benchmark(): started{false} {};
	
	void start();
	
	int stop();
};

#include "benchmark.cpp"