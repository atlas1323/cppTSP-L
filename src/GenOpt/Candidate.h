#pragma once

#include <vector>
#include <random>
#include <string>
#include <memory>



#include "City.h"
#include "Point.h"


class Candidate
{

public:
	// member variables
	std::unique_ptr<City[]> Cities;
	std::unique_ptr<int[]> Indices;
	static std::vector<Point> Points;

	
	
	// Constructors, destructors and associated tools
	Candidate();
	Candidate(const Candidate& that);
	Candidate(Candidate&& that) noexcept;
	~Candidate() = default;


	// Overloaded Operators
	bool operator<(const Candidate& that);
	bool operator>(const Candidate& that);
	Candidate& operator=(const Candidate& that);
    Candidate& operator=(Candidate&& that);


	// Documentation Tools
	std::string PriorityString();
	std::string RouteString();
	std::string LogString();

	// Optimization tools
	void GenerateRandomRoute();
	void SwapMutation();
	void PriorityMut(const double& rate);
	static void Crossover(const Candidate& ParentA, const Candidate& ParentB, Candidate& ChildA, Candidate& ChildB);
	static void Crossover2(const Candidate& ParentA, const Candidate& ParentB, Candidate& ChildA, Candidate& ChildB);



	// Getters and setters
	static int GetEvalCount();
	int GetSize();
	double GetFitness() const;
	double GetPathLength() const;
	void CalcFitness();
	double GetPriority(const int& index)  const;
	void SetPriority(const int& index, const double& priority);


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



