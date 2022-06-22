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


	// Read in dPath
    std::string dPath;
    std::cout << "Dataset Path:\n";
    std::getline(std::cin, dPath);
    
    // Read in oPath
    std::string oPath;
    std::cout << "Datalog Path:\n";
    std::getline(std::cin, oPath);

    // Get number of evaluations to runa
    int num_evals;
    std::cout << "Num Evals:\n";
    std::cin >> num_evals;
    std::cin.ignore(1,'\n');

    // Method selection
    std::string method;
    std::cout << "Method Selection:\n";
    std::getline(std::cin, method);

    if(method == "Random")
    {
        std::cout << "Performing random search...\n";
        Optimizers::RandomSearch(num_evals, dPath, oPath);
    }
    else if (method == "RMHC")
    {
        std::cout << "RMHC selected...\n";

        int pop_size;
        std::cout << "Population size:\n";
        std::cin >> pop_size;
        std::cin.ignore(1,'\n');

        std::cout << "Parameters##############################\n";
        std::cout << "Pop size:  " << pop_size << std::endl;
        std::cout << "Num Evals: " << num_evals << std::endl;

        Optimizers::RMHC(pop_size, num_evals, dPath, oPath);

    }
    else if (method == "BGA1")
    {
        std::cout << "BasicGA1 selected\n";
        
        int pop_size;
        std::cout << "Population size:\n";
        std::cin >> pop_size;
        std::cin.ignore(1,'\n');

        double surivial_rate;
        std::cout << "Survival rate:\n";
        std::cin >> surivial_rate;
        std::cin.ignore(1,'\n');

        std::cout << "Parameters##############################\n";
        std::cout << "Pop size:  " << pop_size << std::endl;
        std::cout << "Num Evals: " << num_evals << std::endl;
        std::cout << "Survival%: " << surivial_rate << std::endl;
        
        Optimizers::BasicGA(pop_size, num_evals, surivial_rate, dPath, oPath);

    }
    else if (method == "BGA2")
    {
        std::cout << "BasicGA2 selected\n";

        int pop_size;
        std::cout << "Population size:\n";
        std::cin >> pop_size;
        std::cin.ignore(1,'\n');

        double surivial_rate;
        std::cout << "Survival rate:\n";
        std::cin >> surivial_rate;
        std::cin.ignore(1, '\n');
        
        std::cout << "Parameters##############################\n";
        std::cout << "Pop size:  " << pop_size << std::endl;
        std::cout << "Num Evals: " << num_evals << std::endl;
        std::cout << "Survival%: " << surivial_rate << std::endl;

        Optimizers::BasicGA2(pop_size, num_evals, surivial_rate, dPath, oPath);
    }
    else if (method == "BGA3")
    {
        std::cout << "BasicGA3 selected\n";

        int pop_size;
        std::cout << "Population size:\n";
        std::cin >> pop_size;
        std::cin.ignore(1,'\n');

        double surivial_rate;
        std::cout << "Survival rate:\n";
        std::cin >> surivial_rate;
        std::cin.ignore(1, '\n');
        
        std::cout << "Parameters##############################\n";
        std::cout << "Pop size:  " << pop_size << std::endl;
        std::cout << "Num Evals: " << num_evals << std::endl;
        std::cout << "Survival%: " << surivial_rate << std::endl;

        Optimizers::BasicGA3(pop_size, num_evals, surivial_rate, dPath, oPath);
    }
    else if (method == "BGA4")
    {
        std::cout << "BasicGA4 selected\n";

        int pop_size;
        std::cout << "Population size:\n";
        std::cin >> pop_size;
        std::cin.ignore(1,'\n');

        double surivial_rate;
        std::cout << "Survival rate:\n";
        std::cin >> surivial_rate;
        std::cin.ignore(1, '\n');

        double restart_rate;
        std::cout << "Restart rate:\n";
        std::cin >> restart_rate;
        std::cin.ignore(1, '\n');
        
        std::cout << "Parameters##############################\n";
        std::cout << "Pop size:  " << pop_size << std::endl;
        std::cout << "Num Evals: " << num_evals << std::endl;
        std::cout << "Survival%: " << surivial_rate << std::endl;
        std::cout << "Restart %: " << restart_rate << std::endl;


        Optimizers::BasicGA4(pop_size, num_evals, surivial_rate, restart_rate, dPath, oPath);
    }
    else if (method == "BGA5")
    {
        std::cout << "BasicGA5 selected\n";

        int pop_size;
        std::cout << "Population size:\n";
        std::cin >> pop_size;
        std::cin.ignore(1,'\n');

        double surivial_rate;
        std::cout << "Survival rate:\n";
        std::cin >> surivial_rate;
        std::cin.ignore(1, '\n');
        
        std::cout << "Parameters##############################\n";
        std::cout << "Pop size:  " << pop_size << std::endl;
        std::cout << "Num Evals: " << num_evals << std::endl;
        std::cout << "Survival%: " << surivial_rate << std::endl;

        Optimizers::BasicGA5(pop_size, num_evals, surivial_rate, dPath, oPath);
    }
    else if (method == "MGA")
    {
        std::cout << "Mut. Gen Alg selected\n";

        int pop_size;
        std::cout << "Population size:\n";
        std::cin >> pop_size;
        std::cin.ignore(1,'\n');

        double surivial_rate;
        std::cout << "Survival rate:\n";
        std::cin >> surivial_rate;
        std::cin.ignore(1, '\n');

        double pressure;
        std::cout << "Mutation Pressure:\n";
        std::cin >> pressure;
        std::cin.ignore(1, '\n');
        
        std::cout << "Parameters##############################\n";
        std::cout << "Pop size:  " << pop_size << std::endl;
        std::cout << "Num Evals: " << num_evals << std::endl;
        std::cout << "Survival%: " << surivial_rate << std::endl;
        std::cout << "Pressure %: " << pressure << std::endl;


        Optimizers::MutGA(pop_size, num_evals, surivial_rate, pressure, dPath, oPath);
    }
    else if (method == "MGAVP")
    {
        std::cout << "Variable Pressure Mut. Gen. Alg selected\n";

        int pop_size;
        std::cout << "Population size:\n";
        std::cin >> pop_size;
        std::cin.ignore(1,'\n');

        double surivial_rate;
        std::cout << "Survival rate:\n";
        std::cin >> surivial_rate;
        std::cin.ignore(1, '\n');

        double low_pressure;
        std::cout << "Lower Bound Mutation Pressure:\n";
        std::cin >> low_pressure;
        std::cin.ignore(1, '\n');

        double high_pressure;
        std::cout << "Upper Bound Mutation Pressure:\n";
        std::cin >> high_pressure;
        std::cin.ignore(1, '\n');

        int slack;
        std::cout << "Slack between LB and HB:\n";
        std::cin >> slack;
        std::cin.ignore(1, '\n');
        
        std::cout << "Parameters##############################\n";
        std::cout << "Pop size:  " << pop_size << std::endl;
        std::cout << "Num Evals: " << num_evals << std::endl;
        std::cout << "Survival%: " << surivial_rate << std::endl;
        std::cout << "LB Pres.%: " << low_pressure << std::endl;
        std::cout << "HB Pres.%: " << high_pressure << std::endl;
        std::cout << "Slack:     " << slack << std::endl;



        Optimizers::MutGA_VP(pop_size, num_evals, surivial_rate, low_pressure, high_pressure, slack, dPath, oPath);
    }
    else if (method == "VarP")
    {
        std::cout << "Variable Survival Pressure selected\n";

        int pop_size;
        std::cout << "Population size:\n";
        std::cin >> pop_size;
        std::cin.ignore(1,'\n');

        double low_pressure;
        std::cout << "Lower Bound Mutation Pressure:\n";
        std::cin >> low_pressure;
        std::cin.ignore(1, '\n');

        double high_pressure;
        std::cout << "Upper Bound Mutation Pressure:\n";
        std::cin >> high_pressure;
        std::cin.ignore(1, '\n');

        int slack;
        std::cout << "Slack between LB and HB:\n";
        std::cin >> slack;
        std::cin.ignore(1, '\n');
        
        std::cout << "Parameters##############################\n";
        std::cout << "Pop size:  " << pop_size << std::endl;
        std::cout << "Num Evals: " << num_evals << std::endl;
        // std::cout << "Survival%: " << surivial_rate << std::endl;
        std::cout << "LB Pres.%: " << low_pressure << std::endl;
        std::cout << "HB Pres.%: " << high_pressure << std::endl;
        std::cout << "Slack:     " << slack << std::endl;



        Optimizers::VariablePressure(pop_size, num_evals, low_pressure, high_pressure, slack, dPath, oPath);
    }
    else
    {
        std::cout << "Invalid method chosen\n";
    }
	return 0;
}