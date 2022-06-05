#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <random>
#include <algorithm>
#include <iterator>
#include <functional>
#include <iterator>
#include <iomanip>
#include <sstream>
#include <filesystem>

#include <math.h>

#include <Benchmarks.h>
#include <DataLog.h>
#include <Contender.h>
#include <Optimizers.h>


int main(int argc, char *argv[])
{
	std::string dPath;
	std::string oPath;
	std::cout << "Current path is " << std::filesystem::current_path() << '\n';
	std::cout << argc << std::endl;
	if (argc > 0)
	{
		dPath = argv[1];
		oPath = argv[2];
	}
	// std::string oPath = "C:\\dev\\cppTSP\\Resources\\Results\\";
	// std::string dPath = "C:\\dev\\cppTSP\\Resources\\DataSets\\circ200.txt";

	std::cout << dPath << std::endl;
	std::cout << oPath << std::endl;

	//std::vector<Point> data = ReadInPoints(dPath);
	//Contender::Points = data;
	/*int size = data.size();*/

	//std::string method = "GeneticAlg";

	//DataLog logger = DataLog(dPath, oPath, "GeneticAlg", "");
	//Optimizers::BasicGA(1000, 300'000, dPath, 0.5f, logger);


	int num_runs = 300'000;

	//Optimizers::RandomSearch(3'000'000, dPath, oPath);
	// Optimizers::BasicGA4(1000, num_runs, 0.5f, 24.0f, dPath, oPath);
	// std::cout << "Continue?";
	// std::cin.get();
	
	// Optimizers::BasicGA2(1000, num_runs, 0.5f, dPath, oPath);
	// std::cout << "Continue?";
	// std::cin.get();
	// Optimizers::RandomSearch(300'000, dPath, oPath);
	Optimizers::BasicGA3(1000, num_runs, 0.5f, dPath, oPath);
	// std::cout << "Continue?";
	// std::cin.get();
	// Optimizers::RMHC(1000, num_runs, dPath, oPath);


	/*DataLog logger = DataLog(dPath, oPath, "RMHC", "P500");
	Optimizers::RMHC(500, 3'000'000, logger);*/

	//DataLog logger = DataLog(dPath, oPath, "GeneticAlg3", "P1000");
	//Optimizers::BasicGA2(1000, 3'000'000, 0.5f, logger);
	//Optimizers::BasicGA3(1000, 3'000'000, 0.5f, logger);

	//Optimizers::BasicGA4(1000, 3'000'000, 0.5f, 10.0f, dPath, oPath);
	std::cout << "here" << std::endl;
	return 0;
}