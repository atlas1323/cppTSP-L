#include "Optimizers.h"

#include "Contender.h"
#include "Candidate.h"
#include "DataLog.h"

#include <random>
#include <vector>
#include <algorithm>
#include <string>
#include <iostream>

namespace Optimizers
{
	std::random_device rand_dev;
	std::mt19937 rng(rand_dev());




	int ProportionalSelection(const std::vector<Contender>& population, const double& sum_fit)
	{
		std::uniform_real_distribution<double> r_dist(0.0f, sum_fit);
		double pick = r_dist(rng);
		double tracker = population[0].GetFitness();
		int index = 0;

		while (tracker < pick)
		{
			index++;
			tracker += population[index].GetFitness();
		}
		return index;
	}


	void BasicGA(int pop_size, int num_evals, double survival_rate, std::string dPath, std::string oPath)
	{
		std::string params = "P:" + std::to_string(pop_size) + " E:" + std::to_string(num_evals) + " SR:" + std::to_string(survival_rate);
		DataLog logger = DataLog(dPath, oPath, "GeneticAlg", params);
		// Delcare and define necessary variables
		double best_fitness;
		double sum_fitness;
		int cutoff = (int)(survival_rate * pop_size);
		std::cout << cutoff << std::endl;


		// collect data
		Contender::Points = logger.GetPoints();


		// Generate starting population
		std::vector<Contender> population;
		for (int i = 0; i < pop_size; i++)
			population.push_back(Contender());

		// Sort starting popultion by fitness and find best fitness
		std::sort(population.begin(), population.end());
		best_fitness = population[0].GetPathLength();
		logger.LogEntry(population[0].LogString());

		for (int i = 0; i < pop_size; i++)
			std::cout << population[i].GetPathLength() << " ";
		std::cout << std::endl;

		// main evolution loop
		while (Contender::GetEvalCount() < num_evals)
		{
			// Get total fitness
			sum_fitness = 0.0f;
			for (int i = 0; i < cutoff; i++)
				sum_fitness += population[i].GetFitness();

			// Generate Solutions: Select and REcombine
			for (int i = cutoff; i < pop_size-1; i+=2)
			{
				int ParentA = ProportionalSelection(population, sum_fitness);
				int ParentB = ParentA;
				while(ParentB == ParentA)
					ParentB = ProportionalSelection(population, sum_fitness);
				Contender::Crossover2(population[ParentA], population[ParentB], population[i], population[i+1]);
			}

			// Creates random solutions if an odd population member is left
			if ((pop_size - cutoff) % 2 != 0)
			{
				population[pop_size - 1].GenerateRandomRoute();
			}

			// Rank
			std::sort(population.begin(), population.end());

			if (population[0].GetPathLength() < best_fitness) {
				best_fitness = population[0].GetPathLength();

				// LOG DATA
				logger.LogEntry(population[0].LogString());
				std::cout << Contender::GetEvalCount() << " : " << population[0].GetPathLength() << std::endl;
			}
		}

		std::cout << Contender::GetEvalCount() << std::endl;
		Contender::ResetEvalCount();
	}

	void BasicGA2(int pop_size, int num_evals, double survival_rate, std::string dPath, std::string oPath)
	{
		std::cout << "BasicGA2 called ############################################################" << std::endl; 
		std::string params = "P:" + std::to_string(pop_size) + " E:" + std::to_string(num_evals) + " SR:" + std::to_string(survival_rate);
		DataLog logger = DataLog(dPath, oPath, "GeneticAlg2", params);
		// Delcare and define necessary variables
		double best_fitness;
		double sum_fitness;
		int cutoff = (int)(survival_rate * pop_size);
		std::cout << cutoff << std::endl;


		// collect data
		Contender::Points = logger.GetPoints();

		// Generate starting population
		std::vector<Contender> population;
		for (int i = 0; i < pop_size; i++)
			population.push_back(Contender());

		for (int i = 0; i < pop_size; i++)
			std::cout << population[i].GetPathLength() << " ";
		std::cout << std::endl;

		//std::cout << "sorting\n\n";

		// Sort starting popultion by fitness and find best fitness
		std::sort(population.begin(), population.end());
		best_fitness = population[0].GetPathLength();
		logger.LogEntry(population[0].LogString());

		for (int i = 0; i < pop_size; i++)
			std::cout << population[i].GetPathLength() << " ";
		std::cout << std::endl;
		// TODO: Log Data

		// main evolution loop
		while (Contender::GetEvalCount() < num_evals)
		{
			bool print = false;
			//if (Contender::GetEvalCount() % 5000 == 0)
			//{
			//	std::cout << Contender::GetEvalCount() << " : ";
			//	//std::cout << Contender::GetEvalCount() << " : " << population[0].LogString() << std::endl;
			//	for (int i = 0; i < pop_size; i++)
			//	{
			//		std::cout << population[i].GetPathLength() << ", ";
			//	}

			//	std::cout << std::endl << std::endl;

			//	print = true;
			//}
			/*for (int i = 0; i < pop_size; i++)
				std::cout << population[i].GetPathLength() << " ";
			std::cout << std::endl;*/
			// Down select ################################################################################
			// Get the sum of fitnesses

			//std::cout << "Summing fitness" << std::endl;
			sum_fitness = 0.0f;
			for (int i = 0; i < cutoff; i++)
				sum_fitness += population[i].GetFitness();

			// Generate Solutions: Select and REcombine
			for (int i = cutoff; i < pop_size - 1; i += 2)
			{
				int ParentA = ProportionalSelection(population, sum_fitness);
				int ParentB = ParentA;
				while (ParentB == ParentA)
					ParentB = ProportionalSelection(population, sum_fitness);
				//if (print)
				//{
				//	//std::cout << cutoff << " " << pop_size -1 << std::endl;
				//	//std::cout << ParentA << " " << ParentB << std::endl;

				//	for (int j = 0; j < population[i].GetSize(); i++)
				//	{
				//		
				//	}
				//}
				Contender::Crossover(population[ParentA], population[ParentB], population[i], population[i + 1]);
			}

			// Creates random solutions if an odd population member is left
			if ((pop_size - cutoff) % 2 != 0)
			{
				population[pop_size - 1].GenerateRandomRoute();
			}

			//std::cout << "sorting" << std::endl;
			// Rank
			std::sort(population.begin(), population.end());

			if (population[0].GetPathLength() < best_fitness) {
				best_fitness = population[0].GetPathLength();

				// LOG DATA
				logger.LogEntry(population[0].LogString());
				std::cout << Contender::GetEvalCount() << " : " << population[0].GetPathLength() << std::endl;
			}
		}

		std::cout << "\n\n\n################################################################################";


		for (Contender member : population)
		{
			std::cout << member.GetPathLength() << " ";
		}

		std::cout << "################################################################################\n\n\n";
		std::cout << Contender::GetEvalCount() << std::endl;
		Contender::ResetEvalCount();
	}

	void BasicGA3(int pop_size, int num_evals, double survival_rate, std::string dPath, std::string oPath)
	{
		std::string params = "P:" + std::to_string(pop_size) + " E:" + std::to_string(num_evals) + " SR:" + std::to_string(survival_rate);
		DataLog logger = DataLog(dPath, oPath, "GeneticAlg3", params);

		// Delcare and define necessary variables
		double best_fitness;
		double sum_fitness;
		int cutoff = (int)(survival_rate * pop_size);
		std::cout << cutoff << std::endl;


		// collect data
		Contender::Points = logger.GetPoints();

		// Generate starting population
		std::vector<Contender> population;
		for (int i = 0; i < pop_size; i++)
			population.push_back(Contender());

		// for (int i = 0; i < pop_size; i++)
		// 	std::cout << population[i].GetPathLength() << " ";
		// std::cout << std::endl;

		std::cout << "sorting\n\n";

		// Sort starting popultion by fitness and find best fitness
		std::sort(population.begin(), population.end());
		best_fitness = population[0].GetPathLength();
		logger.LogEntry(population[0].LogString());

		// for (int i = 0; i < pop_size; i++)
		// 	std::cout << population[i].GetPathLength() << " ";
		// std::cout << std::endl;
		// TODO: Log Data

		// main evolution loop
		while (Contender::GetEvalCount() < num_evals)
		{
			bool print = false;

			sum_fitness = 0.0f;
			for (int i = 0; i < cutoff; i++)
				sum_fitness += population[i].GetFitness();

			// Generate Solutions: Select and REcombine
			for (int i = cutoff; i < pop_size - 3; i += 2)
			{
				int ParentA = ProportionalSelection(population, sum_fitness);
				int ParentB = ParentA;
				while (ParentB == ParentA)
					ParentB = ProportionalSelection(population, sum_fitness);

				Contender::Crossover(population[ParentA], population[ParentB], population[i], population[i + 1]);
			}

			population[pop_size - 2].GenerateRandomRoute();
			population[pop_size - 1].GenerateRandomRoute();

			//std::cout << "sorting" << std::endl;
			// Rank
			std::sort(population.begin(), population.end());

			if (population[0].GetPathLength() < best_fitness) {
				best_fitness = population[0].GetPathLength();

				// LOG DATA
				logger.LogEntry(population[0].LogString());
				std::cout << Contender::GetEvalCount() << " : " << population[0].GetPathLength() << std::endl;
			}
		}

		std::cout << "\n\n\n################################################################################\n";


		for (Contender member : population)
		{
			std::cout << member.GetPathLength() << " ";
		}

		// for (int i = 0; i < pop_size; i++)
		// {
		// 	std::cout << "\n" << i << "---" << population[i].GetPathLength() << "\n";
		// 	std::cout << population[i].RouteString() << std::endl;
		// }
		std::cout << std::endl;

		std::cout << "################################################################################\n\n\n";

		std::cout << Contender::GetEvalCount() << std::endl;
		Contender::ResetEvalCount();
	}

	void BasicGA4(int pop_size, int num_evals, double survival_rate, double restart_rate, std::string dPath, std::string oPath)
	{

		std::string params = "P:" + std::to_string(pop_size) + " E:" + std::to_string(num_evals) + " SR:" + std::to_string(survival_rate) + " RR:" + std::to_string(restart_rate);
		std::uniform_real_distribution<double> r_dist(0.0f, 100.0f);
		double restart;
		DataLog logger = DataLog(dPath, oPath, "GeneticAlg4", params);


		// Delcare and define necessary variables
		double best_fitness;
		double sum_fitness;
		int cutoff = (int)(survival_rate * pop_size);
		std::cout << cutoff << std::endl;


		// collect data
		Contender::Points = logger.GetPoints();

		// Generate starting population
		std::vector<Contender> population;
		for (int i = 0; i < pop_size; i++)
			population.push_back(Contender());

		for (int i = 0; i < pop_size; i++)
			std::cout << population[i].GetPathLength() << " ";
		std::cout << std::endl;

		//std::cout << "sorting\n\n";

		// Sort starting popultion by fitness and find best fitness
		std::sort(population.begin(), population.end());
		best_fitness = population[0].GetPathLength();
		logger.LogEntry(population[0].LogString());

		for (int i = 0; i < pop_size; i++)
			std::cout << population[i].GetPathLength() << " ";
		std::cout << std::endl;
		// TODO: Log Data

		double r_count = 0;
		double round = 0;

		// main evolution loop
		while (Contender::GetEvalCount() < num_evals)
		{
			bool print = false;

			sum_fitness = 0.0f;
			for (int i = 0; i < cutoff; i++)
				sum_fitness += population[i].GetFitness();
			round++;
			// Generate Solutions: Select and REcombine
			for (int i = cutoff; i < pop_size - 1; i += 2)
			{
				restart = r_dist(rng);
				if (restart < restart_rate)
				{
					r_count++;
					//std::cout << "restarting" << std::endl;
					population[i].GenerateRandomRoute();
					population[i+1].GenerateRandomRoute();
				}
				else
				{
					int ParentA = ProportionalSelection(population, sum_fitness);
					int ParentB = ParentA;
					while (ParentB == ParentA)
						ParentB = ProportionalSelection(population, sum_fitness);

					Contender::Crossover(population[ParentA], population[ParentB], population[i], population[i + 1]);
				}
			}

			

			//std::cout << "sorting" << std::endl;
			// Rank
			std::sort(population.begin(), population.end());

			if (population[0].GetPathLength() < best_fitness) {
				best_fitness = population[0].GetPathLength();

				// LOG DATA
				logger.LogEntry(population[0].LogString());
				std::cout << Contender::GetEvalCount() << " : " << population[0].GetPathLength() << std::endl;
			}
		}
		double avg = r_count / round;
		std::cout << avg << std::endl;
		std::cout << "\n\n\n################################################################################";


		for (Contender member : population)
		{
			std::cout << member.GetPathLength() << " ";
		}

		std::cout << "################################################################################\n\n\n";
		std::cout << Contender::GetEvalCount() << std::endl;
		Contender::ResetEvalCount();
	}


	void RMHC(int pop_size, int num_evals, std::string dPath, std::string oPath)
	{
		std::string params = "P:" + std::to_string(pop_size) + " E:" + std::to_string(num_evals);
		DataLog logger = DataLog(dPath, oPath, "RMHC", params);

		std::cout << "Beggining trial" << std::endl;
		// Define tracking variables
		int best_fitness = 0;

		std::cout << "Generating Population... " << std::endl;
		// Generate population
		Contender::Points = logger.GetPoints();
		std::vector <Contender> population;

		for (int i = 0; i < pop_size; i++)
		{
			population.push_back(Contender());
			if (population[i] < population[best_fitness] || i == best_fitness)
			{

				best_fitness = i;
				logger.LogEntry(population[best_fitness].LogString());
				std::cout << Contender::GetEvalCount() << " : " << population[best_fitness].GetPathLength() << std::endl;
			}
		}
		

		// logger.LogEntry(population[best_fitness].LogString());
		// std::cout << Contender::GetEvalCount() << " : " << population[best_fitness].GetPathLength() << std::endl;

		std::cout << "starting opt loop" << std::endl;
		// Begin optimization loop
		while (Contender::GetEvalCount() < num_evals)
		{
			std::cout << Contender::GetEvalCount() << std::endl;
			for (int i = 0; i < pop_size; i++)
			{
				Contender temp = Contender(population[i]);
				temp.SwapMutation();
				temp.CalcFitness();
				if (temp < population[i])
				{
					population[i] = temp;
					if (population[i] < population[best_fitness] || i == best_fitness)
					{
						best_fitness = i;
						logger.LogEntry(population[best_fitness].LogString());
						std::cout << Contender::GetEvalCount() << " ::: " << population[best_fitness].GetPathLength() << std::endl;

					}
				}
			}
		}
		std::cout << Contender::GetEvalCount() << std::endl;
		Contender::ResetEvalCount();
	}

	void RandomSearch(int num_evals, std::string dPath, std::string oPath)
	{
		std::string params = " E:" + std::to_string(num_evals);


		DataLog logger = DataLog(dPath, oPath, "RandomSearch", params);
		// Generate Population
		Contender::Points = logger.GetPoints();
		
		// Define tracking variables
		Contender best_fitness = Contender();
		logger.LogEntry(best_fitness.LogString());
		std::cout << Contender::GetEvalCount() << " : " << best_fitness.GetPathLength() << std::endl;


		for (int i = 1; i < num_evals; i++)
		{
			Contender temp = Contender();
			if (temp < best_fitness)
			{
				best_fitness = temp;
				logger.LogEntry(best_fitness.LogString());
				std::cout << Contender::GetEvalCount() << " : " << best_fitness.GetPathLength() << std::endl;
			}
		}

		std::cout << Contender::GetEvalCount() << std::endl;
		Contender::ResetEvalCount();
	}
}

