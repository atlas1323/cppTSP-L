#include "Contender.h"
#include "Point.h"
#include "City.h"

#include <math.h>
#include <assert.h>

#include <iostream>
#include <algorithm>
#include <vector>
#include <random>
#include <string>



// ################################################################################
// Static member variable initialization (where feasible)
// ################################################################################

int Contender::evaluations_ = 0;

// define RGN devices
std::random_device Contender::rand_dev_;
std::mt19937 Contender::rng_(Contender::rand_dev_());
std::vector<Point> Contender::Points;

// ################################################################################
// Constructors and constructor tools
// ################################################################################


Contender::Contender()
{
	this->size_ = Points.size();
	Cities = new City[size_];
	Indices = new int[size_];
	for (int i = 0; i < size_; i++)
		Indices[i] = i;

	// Populate variables
	GenerateRandomRoute();
	//CalcFitness(); // Fitness will get calculated in RandomRoute
}

/// <summary>
/// Copy constructor for contender
/// </summary>
/// <param name="that">Contender object to be copied</param>
Contender::Contender(const Contender& that)
	:	fitness_{ that.fitness_},
		path_length_{that.path_length_},
		size_{that.size_},
		Indices{new int[that.size_]},
		Cities{new City[that.size_]}
{
	for (size_t i = 0; i < that.size_; i++)
	{
		this->Indices[i] = that.Indices[i];
		this->Cities[i] = that.Cities[i];
	}
	
}

Contender::Contender(Contender&& that) noexcept
	:	size_{that.size_},
		fitness_{that.fitness_},
		path_length_{that.path_length_},
		Indices{that.Indices},
		Cities{that.Cities}
{
	that.size_ = 0;
	that.fitness_ = 0;
	that.path_length_ = 0;
	that.Indices = nullptr;
	that.Cities = nullptr;
}


/// <summary>
/// Cleans up memory allocated on heap
/// </summary>
Contender::~Contender()
{
	// std::cout << path_length_ << std::endl;

	delete[] Indices;
	delete[] Cities;
}


// ################################################################################
// Overloaded Operators
// ################################################################################

/// <summary>
/// Comparison operator for sorting
/// </summary>
/// <param name="that">contender to compare this instance to</param>
/// <returns>Boolean evaluation of this fitness < that fitness</returns>
bool Contender::operator<(const Contender& that)
{
	return this->path_length_ < that.path_length_;
}

/**
 * @brief Greather or equal to operator used for sorting
 * 
 * @param that : RHS contender to compare to
 * @return true : LHS contender is larger than RHS contender
 * @return false : LHS contender is smaller than RHS contender
 */
bool Contender::operator>(const Contender& that)
{
	return this->path_length_ > that.path_length_;
}




/**
 * @brief Copy Assignment
 * 
 * @param that Instance to copy
 * @return Contender& 
 */
Contender& Contender::operator=(const Contender& that)
{
	if (this != &that)
	{
		// const auto new_indices = new int[that.size_];
		// const auto new_cities = new City[that.size_];

		delete[] this->Indices;
		delete[] this->Cities;

		this->size_ = that.size_;
		this->fitness_ = that.fitness_;
		this->path_length_ = that.path_length_;

		if (that.size_ > 0)
		{
			this->Indices = new int[that.size_];
			this->Cities = new City[that.size_];

			for (size_t i = 0; i < that.size_; i++)
			{
				this->Indices[i] = that.Indices[i];
				this->Cities[i] = that.Cities[i];
			}
		}
		else
		{
			this->Indices = nullptr;
			this->Cities = nullptr;
		}


		

	}
	return *this;
}

Contender& Contender::operator=(Contender&& that)
{
	if (this != &that)
	{
		delete[] this->Indices;
		delete[] this->Cities;
		this->Indices = that.Indices;
		this->Cities = that.Cities;

		this->fitness_ = that.fitness_;
		this->path_length_ = that.path_length_;
		this->size_ = that.size_;

		that.path_length_=0;
		that.fitness_ = 0;
		that.size_ = 0;
		that.Indices = nullptr;
		that.Cities = nullptr;
	}
	return *this;
}


// ################################################################################
// Documentation Tools
// ################################################################################

std::string Contender::PriorityString()
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
std::string Contender::RouteString()
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
std::string Contender::LogString()
{
	std::string log_string = std::to_string(evaluations_) + " | " + std::to_string(path_length_) + " | " + RouteString();

	return log_string;

}


// ################################################################################
// Optimization tools
// ################################################################################



/// <summary>
/// Method for filling cities with requisite information. Assumes the cities object has been declared
/// and memory allocated for city objects
/// </summary>
void Contender::GenerateRandomRoute()
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
void Contender::SwapMutation()
{
	// Swaps index/indices to prevent

	std::uniform_int_distribution<int> dist(0, size_-1);
	int index1 = dist(rng_);
	int index2 = index1;
	while (index2 == index1)
	{
		index2 = dist(rng_);
	}
	
	double temp = Cities[index1].priority;
	Cities[index1].priority = Cities[index2].priority;
	Cities[index2].priority = temp;
	// Cities[index1] = City(Cities[index1].index, Cities[index2].priority);
	// Cities[index2] = City(Cities[index2].index, temp);
}

void Contender::ReverseMutation()
{
	std::reverse(Cities, Cities + size_);
	for (int i = 0; i < size_; i++)
	{
		double p = 0.0f + i;
		Cities[i].priority = p;
	}
	UpdateIndices();

}

/// <summary>
/// Mutation for priority list to increment or decrement its value. Each locus has a 
/// chance of mutation equal to the user define rate. It will then be incremented or decremented
/// by one to mutate it's order. 
/// </summary>
/// <param name="rate">Mutation rate</param>
void Contender::PriorityMut(const double& rate)
{
	std::uniform_real_distribution<double> dist(0.0f, 100.0f);
	for (int i = 0; i < size_; i++)
	{
		if (dist(rng_) < rate)
		{
			int p = GetPriority(i);
			if (dist(rng_) < 50.0f)
				p+=2;
			else
				p-=2;
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
void Contender::Crossover(const Contender& ParentA, const Contender& ParentB, Contender& ChildA, Contender& ChildB)
{
	int size_ = ParentA.size_;

	// Generate crossover points
	std::uniform_int_distribution<int> dist(0, size_-1);
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
void Contender::Crossover2(const Contender& ParentA, const Contender& ParentB, Contender& ChildA, Contender& ChildB)
{
	int size_ = ParentA.size_;

	// Generate crossover points
	std::uniform_int_distribution<int> dist(0, size_-1);
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

int Contender::GetEvalCount()
{
	return evaluations_;
}

int Contender::GetSize()
{
	return this->size_;
}

/// <summary>
/// Calculates total path length as a measure of fitness for the path.
/// (will use 1 - fit/total for actual fitness metric)
/// Updates fitness_ member variable when done
/// </summary>
void Contender::CalcFitness()
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

double Contender::GetPathLength() const
{
	return path_length_;
}

double Contender::GetFitness() const
{
	return fitness_;
}


/// <summary>
/// Quick function to get the priority at a given city index
/// </summary>
/// <param name="index">index desired</param>
/// <returns></returns>
double Contender::GetPriority(const int& index) const
{
	// std::cout << Indices[index] << std::endl;
	return Cities[Indices[index]].priority;
}


/// <summary>
/// Basically alias to quickly set priority at a specific index
/// </summary>
/// <param name="index"></param>
/// <param name="priority"></param>
void Contender::SetPriority(const int& index, const double& priority)
{
	Cities[Indices[index]].priority = priority;
}

// Resets count to 0 so the experiments can continue!!!!! Woo!!!!
void Contender::ResetEvalCount()
{
	evaluations_ = 0;
}

// ################################################################################
// Debugging Methods
// ################################################################################



// ################################################################################
// Private Methods
// ################################################################################

/// <summary>
/// Calculates the euclidean distance between two Point objects
/// </summary>
/// <param name="a">First point</param>
/// <param name="b">Second point</param>
/// <returns></returns>
double Contender::EucDist(const Point& a, const Point& b)
{
	// Euclidean Distance formula
	double distance = sqrt(pow(a.x - b.x, 2) + pow(a.y - b.y, 2));
	return distance;
}

/// <summary>
/// Updates the indices list for reverse mapping needed in crossover.
/// Reduces need for "sorting" lists repeatedly on index vs priority and runs in O(n) time
/// </summary>
void Contender::UpdateIndices()
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
void Contender::SortCities()
{
	std::sort(Cities, Cities + size_);
	for (int i = 0; i < size_; i++)
	{
		double p = 0.0f + i;
		Cities[i].priority = p;
	}
	UpdateIndices();
}