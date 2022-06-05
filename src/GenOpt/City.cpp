
#include <City.h>

#include <iostream>

/// <summary>
/// Comparison operator for sorting cities by priority.
/// </summary>
/// <param name="that">City to compare to</param>
/// <returns>priority of THIS city < priority of THAT city</returns>
bool City::operator<(const City& that)
{
	return priority < that.priority;
}

/// <summary>
/// Default constructor
/// </summary>
City::City()
{
	this->index = -1;
	this->priority = -1.0f;
}

/// <summary>
/// Constructor for when supplied index and priority
/// </summary>
/// <param name="index"></param>
/// <param name="priority"></param>
City::City(int index, double priority)
{
	this->index = index;
	this->priority = priority;
}


// City::~City()
// {
// 	std::cout << "destroying " << index << std::endl; 
// }