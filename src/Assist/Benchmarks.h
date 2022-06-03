#pragma once
#include <chrono>

class Timer
{
public:
	Timer(const char* name);
	~Timer();
private:
	std::chrono::time_point< std::chrono::high_resolution_clock> m_StartMarker;
	const char* m_name;
};