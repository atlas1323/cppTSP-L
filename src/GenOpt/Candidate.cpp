#include "Candidate.h"
#include "City.h"
#include "Point.h"

#include <math.h>

#include <iostream>
#include <algorithm>
#include <vector>
#include <random>
#include <string>
#include <memory>





// ################################################################################
// Static member variable initialization (where feasible)
// ################################################################################

int Candidate::evaluations_ = 0;

// define RGN devices
std::random_device Candidate::rand_dev_;
std::mt19937 Candidate::rng_(Candidate::rand_dev_());
std::vector<Point> Candidate::Points;

// ################################################################################
// Constructors and constructor tools
// ################################################################################

Candidate::Candidate()
{
    size_ = Points.size();
    Cities = std::make_unique<City[]>(size_);
    Indices = std::make_unique<int[]>(size_);
    for (int i = 0; i < size_; i++)
        Indices[i] = i;
    
    GenerateRandomRoute();
}


// Copy Constructor
Candidate::Candidate(const Candidate& that)
{

    this->fitness_ = that.fitness_;
    this->path_length_ = that.path_length_;
    this->size_ = that.size_;
    this->Cities = std::make_unique<City[]>(size_);
    this->Indices = std::make_unique<int[]>(size_);

    std::copy_n(that.Cities.get(), that.size_, this->Cities.get());
    std::copy_n(that.Indices.get(), that.size_, this->Indices.get());
}

// Move Constructor
Candidate::Candidate(Candidate&& that) noexcept
{
    this->Cities = nullptr;
    this->Cities = nullptr;

    *this = that;
}

// ################################################################################
// Operator Overloads
// ################################################################################

// Copy assignment operator
Candidate& Candidate::operator=(const Candidate& that)
{
    this->fitness_ = that.fitness_;
    this->path_length_ = that.path_length_;
    this->size_ = that.size_;
    this->Cities = std::make_unique<City[]>(size_);
    this->Indices = std::make_unique<int[]>(size_);

    std::copy_n(that.Cities.get(), that.size_, this->Cities.get());
    std::copy_n(that.Indices.get(), that.size_, this->Indices.get());

    return *this;
}

// Move assignment operator
Candidate& Candidate::operator=(Candidate&& that)
{
    this->Cities = nullptr;
    this->Cities = nullptr;
    this->fitness_ = that.fitness_;
    this->path_length_ = that.path_length_;
    this->size_ = that.size_;
    
    std::swap(this->Cities, that.Cities);
    std::swap(this->Indices, that.Indices);

    return *this;
}

// Comparison operator <
bool Candidate::operator<(const Candidate& that)
{
	return this->path_length_ < that.path_length_;
}

// Comparison operator >
bool Candidate::operator>(const Candidate& that)
{
	return this->path_length_ > that.path_length_;
}

// ################################################################################
// Documentation Tools
// ################################################################################


std::string Candidate::PriorityString()
{
	std::string priority_string;
	for (int i = 0; i < size_; i++)
	{
		priority_string += std::to_string(Cities[i].priority);
		priority_string += " ";
	}

	return priority_string;
}

/// <summary>
/// Creates a string containing the path separated by spaces
/// </summary>
/// <returns></returns>
std::string Candidate::RouteString()
{
	std::string route_string;
	for (int i = 0; i < size_; i++)
	{
		route_string += std::to_string(Cities[i].index);
		route_string += " ";
	}

	return route_string;
}

/// <summary>
/// Creates a string for logging evaluation entry
/// </summary>
/// <returns></returns>
std::string Candidate::LogString()
{
	std::string log_string = std::to_string(evaluations_) + " | " + std::to_string(path_length_) + " | " + RouteString();

	return log_string;

}

// ################################################################################
// Optimization Tools
// ################################################################################


/// <summary>
/// Method for filling cities with requisite information. Assumes the cities object has been declared
/// and memory allocated for city objects
/// </summary>
void Candidate::GenerateRandomRoute()
{
	// Create distribution for random generation
	std::uniform_real_distribution<double> dist(0.0f, 1.0f);

	//std::uniform_int_distribution<int> dist(0, size_);
	for (int i = 0; i < size_; i++)
	{
		Cities[i] = City(i, dist(rng_));
	}

	//SortCities();
	CalcFitness();
}

/// <summary>
/// Mutation that randomly swaps genes
/// </summary>
void Candidate::SwapMutation()
{
	// Swaps index/indices to prevent

	std::uniform_int_distribution<int> dist(0, size_);
	int index1 = dist(rng_);
	int index2 = index1;
	while (index2 == index1)
	{
		index2 = dist(rng_);
	}
	
	double temp = Cities[index1].priority;
	Cities[index1].priority = Cities[index2].priority;
	Cities[index2].priority = temp;
}

/// <summary>
/// Mutation for priority list to increment or decrement its value. Each locus has a 
/// chance of mutation equal to the user define rate. It will then be incremented or decremented
/// by one to mutate it's order. 
/// </summary>
/// <param name="rate">Mutation rate</param>
void Candidate::PriorityMut(const double& rate)
{
	std::uniform_real_distribution<double> dist(0.0f, 100.0f);
	for (int i = 0; i < size_; i++)
	{
		if (dist(rng_) < rate)
		{
			int p = GetPriority(i);
			if (dist(rng_) < 50.0f)
				p++;
			else
				p--;
			SetPriority(i, p);
		}
	}

	SortCities();
}


/// <summary>
/// Crossover between ParentA and ParentB applied to ChildA and ChildB
/// </summary>
/// <param name="ParentA"></param>
/// <param name="ParentB"></param>
/// <param name="ChildA"></param>
/// <param name="ChildB"></param>
void Candidate::Crossover(const Candidate& ParentA, const Candidate& ParentB, Candidate& ChildA, Candidate& ChildB)
{
	int size_ = ParentA.size_;

	// Generate crossover points
	std::uniform_int_distribution<int> dist(0, size_);
	int cross_point_a = dist(rng_);
	int cross_point_b = dist(rng_);

	bool flip = false;

	// iterate through points and create 2 crossover children
	for (int i = 0; i < size_; i++)
	{
		if (i == cross_point_a || i == cross_point_b)
			flip = !flip;

		//std::cout << flip << " ##############################################" << std::endl;
		//std::cout << ParentA.GetPriority(i) << " : " << ParentB.GetPriority(i) << " : " << ChildA.GetPriority(i) << " : " << ChildB.GetPriority(i) << std::endl;

		if (flip)
		{
			ChildA.SetPriority(i, ParentA.GetPriority(i));
			ChildB.SetPriority(i, ParentB.GetPriority(i));
		}

		else
		{
			ChildA.SetPriority(i, ParentB.GetPriority(i));
			ChildB.SetPriority(i, ParentA.GetPriority(i));

		}
		//std::cout << ParentA.GetPriority(i) << " : " << ParentB.GetPriority(i) << " : " << ChildA.GetPriority(i) << " : " << ChildB.GetPriority(i) << std::endl;

	}

	ChildA.CalcFitness();
	ChildB.CalcFitness();

	if (ChildA.GetPathLength() == ParentA.GetPathLength() || ChildA.GetPathLength() == ParentB.GetPathLength())
	{
		ChildA.SwapMutation();
		ChildA.CalcFitness();
	}
	if (ChildB.GetPathLength() == ParentA.GetPathLength() || ChildB.GetPathLength() == ParentB.GetPathLength())
	{
		ChildB.SwapMutation();
		ChildB.CalcFitness();
	}

	//for(int i = 0; i < )
}


/// <summary>
/// Like crossover, but not realligning the points
/// </summary>
/// <param name="ParentA"></param>
/// <param name="ParentB"></param>
/// <param name="ChildA"></param>
/// <param name="ChildB"></param>
void Candidate::Crossover2(const Candidate& ParentA, const Candidate& ParentB, Candidate& ChildA, Candidate& ChildB)
{
	int size_ = ParentA.size_;

	// Generate crossover points
	std::uniform_int_distribution<int> dist(0, size_);
	int cross_point_a = dist(rng_);
	int cross_point_b = dist(rng_);

	bool flip = false;

	// iterate through points and create 2 crossover children
	for (int i = 0; i < size_; i++)
	{
		if (i == cross_point_a || i == cross_point_b)
			flip = !flip;

		//std::cout << flip << " ##############################################" << std::endl;
		//std::cout << ParentA.GetPriority(i) << " : " << ParentB.GetPriority(i) << " : " << ChildA.GetPriority(i) << " : " << ChildB.GetPriority(i) << std::endl;

		if (flip)
		{

			ChildA.Cities[i].priority = ParentA.Cities[i].priority;
			ChildB.Cities[i].priority = ParentB.Cities[i].priority;

		}

		else
		{
			ChildA.Cities[i].priority = ParentB.Cities[i].priority;
			ChildB.Cities[i].priority = ParentA.Cities[i].priority;

		}
		//std::cout << ParentA.GetPriority(i) << " : " << ParentB.GetPriority(i) << " : " << ChildA.GetPriority(i) << " : " << ChildB.GetPriority(i) << std::endl;

	}

	ChildA.CalcFitness();
	ChildB.CalcFitness();

	if (ChildA.GetPathLength() == ParentA.GetPathLength() || ChildA.GetPathLength() == ParentB.GetPathLength())
	{
		ChildA.SwapMutation();
		ChildA.CalcFitness();
	}
	if (ChildB.GetPathLength() == ParentA.GetPathLength() || ChildB.GetPathLength() == ParentB.GetPathLength())
	{
		ChildB.SwapMutation();
		ChildB.CalcFitness();
	}
}


// ################################################################################
// Getters and setters
// ################################################################################

int Candidate::GetEvalCount()
{
	return evaluations_;
}

int Candidate::GetSize()
{
	return this->size_;
}


/// <summary>
/// Calculates total path length as a measure of fitness for the path.
/// (will use 1 - fit/total for actual fitness metric)
/// Updates fitness_ member variable when done
/// </summary>
void Candidate::CalcFitness()
{
	evaluations_++;
	this->SortCities();
	double path_length = 0.0f;

	for (int i = 1; i < size_; i++)
	{
		path_length += EucDist(Points[Cities[i].index], Points[Cities[i - 1].index]);
	}

	this->fitness_ = 1.0f/path_length;
	this->path_length_ = path_length;
}

double Candidate::GetPathLength() const
{
	return path_length_;
}

double Candidate::GetFitness() const
{
	return fitness_;
}


/// <summary>
/// Quick function to get the priority at a given city index
/// </summary>
/// <param name="index">index desired</param>
/// <returns></returns>
double Candidate::GetPriority(const int& index) const
{
	// std::cout << Indices[index] << std::endl;
	return Cities[Indices[index]].priority;
}


/// <summary>
/// Basically alias to quickly set priority at a specific index
/// </summary>
/// <param name="index"></param>
/// <param name="priority"></param>
void Candidate::SetPriority(const int& index, const double& priority)
{
	Cities[Indices[index]].priority = priority;
}

// ################################################################################
// Private Methods
// ################################################################################

/// <summary>
/// Calculates the euclidean distance between two Point objects
/// </summary>
/// <param name="a">First point</param>
/// <param name="b">Second point</param>
/// <returns></returns>
double Candidate::EucDist(const Point& a, const Point& b)
{
	// Euclidean Distance formula
	double distance = sqrt(pow(a.x - b.x, 2) + pow(a.y - b.y, 2));
	return distance;
}

/// <summary>
/// Updates the indices list for reverse mapping needed in crossover.
/// Reduces need for "sorting" lists repeatedly on index vs priority and runs in O(n) time
/// </summary>
void Candidate::UpdateIndices()
{
	for (int i = 0; i < size_; i++)
	{
		Indices[Cities[i].index] = i;
	}
}

/// <summary>
/// Sorts the cities and updates the indices, as the cities should never change order without
/// updating indices anyway.
/// </summary>
void Candidate::SortCities()
{
	std::sort(Cities.get(), Cities.get() + size_);
	for (int i = 0; i < size_; i++)
	{
		double p = 0.0f + i;
		Cities[i].priority = p;
	}
	UpdateIndices();
}