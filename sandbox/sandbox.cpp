#include <iostream>
#include <string>
// #include <Optimizers.h>

// #include <City.h>


int main(int argc, char const *argv[])
{
    
    // std::string a = "test 123";
    // std::string b = "hey";
    // std::string input;

    // std::cout << (a == b) << std::endl;
    // std::cout << "enter text: ";
    // std::getline(std::cin, input);
    // std::cout << (a == input) << std::endl;
    // std::cout << input << std::endl;

    // std::cout << "enter text: ";
    // std::getline(std::cin, input);
    // std::cout << input << std::endl;

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
        // Optimizers::RandomSearch(num_evals, dPath, oPath);
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

        // Optimizers::RMHC(pop_size, num_evals, dPath, oPath);

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
        
        // Optimizers::BasicGA(pop_size, num_evals, surivial_rate, dPath, oPath);

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

        // Optimizers::BasicGA2(pop_size, num_evals, surivial_rate, dPath, oPath);
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

        // Optimizers::BasicGA3(pop_size, num_evals, surivial_rate, dPath, oPath);
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


        // Optimizers::BasicGA4(pop_size, num_evals, surivial_rate, restart_rate, dPath, oPath);
    }
    else
    {
        std::cout << "Invalid method chosen\n";
    }

    return 0;
}
