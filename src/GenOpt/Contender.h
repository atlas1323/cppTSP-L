#pragma once

#include <vector>
#include <random>
#include <string>


#include "City.h"
#include "Point.h"

class Contender
{

public:
	// member variables
	City* Cities;
	int* Indices;
	static std::vector<Point> Points;


	// Constructors, destructors and associated tools
	Contender();
	Contender(const Contender& that);
	Contender(Contender&& that) noexcept;
	~Contender();


	// Overloaded Operators
	bool operator<(const Contender& that);
	bool operator>(const Contender& that);
	Contender& operator=(const Contender& that);
	Contender& operator=(Contender&& that);


	// Documentation Tools
	std::string PriorityString();
	std::string RouteString();
	std::string LogString();

	// Optomization tools
	void GenerateRandomRoute();
	void SwapMutation();
	void ReverseMutation();

	void PriorityMut(const double& rate);
	static void Crossover(const Contender& ParentA, const Contender& ParentB, Contender& ChildA, Contender& ChildB);
	static void Crossover2(const Contender& ParentA, const Contender& ParentB, Contender& ChildA, Contender& ChildB);

	// Getters and setters
	static int GetEvalCount();
	int GetSize();
	double GetFitness() const;
	double GetPathLength() const;
	void CalcFitness();
	double GetPriority(const int& index)  const;
	void SetPriority(const int& index, const double& priority);
	static void ResetEvalCount();


	// Debugging
#ifdef _DEBUG
	void SetRoute(const int*& route);
#endif // _DEBUG


private:
	double fitness_;
	double path_length_;
	int size_;
	static int evaluations_;
	static std::random_device rand_dev_;
	static const unsigned Rand_Seed_;
	static std::mt19937 rng_;

	static double EucDist(const Point& a, const Point& b);
	void UpdateIndices();
	void SortCities();


};



