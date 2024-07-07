#include "stopwatch.hpp"

void StopWatch::start()
{
	startTime = std::chrono::high_resolution_clock::now();
}

void StopWatch::stop()
{
	endTime = std::chrono::high_resolution_clock::now();
}

double StopWatch::elapsedNanoseconds()
{
	return std::chrono::duration<double, std::nano>(endTime - startTime).count();
}

double StopWatch::elapsedMicroseconds()
{
	return std::chrono::duration<double, std::micro>(endTime - startTime).count();
}

double StopWatch::elapsedMilliseconds()
{
	return std::chrono::duration<double, std::milli>(endTime - startTime).count();
}
