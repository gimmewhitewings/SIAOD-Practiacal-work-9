#pragma once

#include <thread>
#include <iostream>

class Timer
{
public:
	Timer();
	~Timer();

private:
	std::chrono::time_point<std::chrono::steady_clock> start, end;
};

Timer::Timer()
{
	start = std::chrono::high_resolution_clock::now();
}

Timer::~Timer()
{
	end = std::chrono::high_resolution_clock::now();
	std::chrono::duration<double> duration = end - start;
	std::cout << "Время выполнения: " << duration.count() << " c\n";
}