#pragma once
#include <chrono>

class StopWatch
{
public:
	void start();
	void stop();
	double elapsedNanoseconds();
	double elapsedMicroseconds();
	double elapsedMilliseconds();

private:
	std::chrono::time_point<std::chrono::high_resolution_clock> startTime;
	std::chrono::time_point<std::chrono::high_resolution_clock> endTime;
};
