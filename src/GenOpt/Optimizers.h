#pragma once
#include <string>

namespace Optimizers
{
	void BasicGA(int pop_size, int num_evals, double survival_rate, std::string dPath, std::string oPath);
	void BasicGA2(int pop_size, int num_evals, double survival_rate, std::string dPath, std::string oPath);
	void BasicGA3(int pop_size, int num_evals, double survival_rate, std::string dPath, std::string oPath);
	void BasicGA4(int pop_size, int num_evals, double survival_rate, double restart_rate, std::string dPath, std::string oPath);
	void BasicGA5(int pop_size, int num_evals, double survival_rate, std::string dPath, std::string oPath);
	void RMHC(int pop_size, int num_evals, std::string dPath, std::string oPath);
	void MutGA(int pop_size, int num_evals, double survival_rate, double pressure, std::string dPath, std::string oPath);
	void MutGA_VP(int pop_size, int num_evals, double survival_rate, double low_pressure, double high_pressure, int slack, std::string dPath, std::string oPath );
	void VariablePressure(int pop_size, int num_evals, double l_bound, double h_bound, int slack, std::string dPath, std::string oPath );


	void RandomSearch(int num_evals, std::string dPath, std::string oPath);


}