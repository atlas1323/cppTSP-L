#pragma once

struct City
{
	int index;
	double priority;

	City();
	City(int index, double priority);
	bool operator<(const City& that);
	// ~City();
};