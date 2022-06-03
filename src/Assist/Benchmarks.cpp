#include <Benchmarks.h>
#include <chrono>
#include <iostream>

Timer::Timer(const char* name)
	{
		m_name = name;
		m_StartMarker = std::chrono::high_resolution_clock::now();
	}

Timer::~Timer()
	{
		auto endMaker = std::chrono::high_resolution_clock::now();
		auto start = std::chrono::time_point_cast<std::chrono::microseconds>(m_StartMarker).time_since_epoch().count();
		auto end = std::chrono::time_point_cast<std::chrono::microseconds>(endMaker).time_since_epoch().count();

		double time = end - start;
		double ms = 0.001 * time;

		std::cout << m_name << ": " << time << "us (" << ms << "ms)\n";
	}