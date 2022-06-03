#pragma once
#include <string>
#include <DataLog.h>


namespace Optimizers
{
	void BasicGA(int pop_size, int num_evals, double survival_rate, std::string dPath, std::string oPath);
	void BasicGA2(int pop_size, int num_evals, double survival_rate, std::string dPath, std::string oPath);
	void BasicGA3(int pop_size, int num_evals, double survival_rate, std::string dPath, std::string oPath);
	void BasicGA4(int pop_size, int num_evals, double survival_rate, double restart_rate, std::string dPath, std::string oPath);
	void RMHC(int pop_size, int num_evals, DataLog logger);
	void RandomSearch(int num_evals, std::string dPath, std::string oPath);


}