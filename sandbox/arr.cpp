#include  <iostream>
#include <random>

int main(){
    // int bob[] = {1, 2, 3, 4, 5, 6};
    // int* finn = &bob[2];

    // std::cout << *finn << std::endl;
    // *finn = 200;
    // std::cout << std::endl;
    // for(int i : bob)
    // {
    //     std::cout << i << " ";
    // }
    // std::cout << std::endl;

    enum tester {ALPHA, BETA, GAMMA, ETA};
    std::random_device rando;
    std::mt19937 rng(rando());
    std::uniform_int_distribution<int> dist(ALPHA, ETA);
    // std::static_
    int num = dist(rng);
    // tester e = static_cast<tester>(num);
    tester e = (tester)num;
    
    
    switch(e) {
        case ALPHA :
            std::cout << "ALPHA" << std::endl;
            break;
        case BETA :
            std::cout << "BETA" << std::endl;
            break;
        case GAMMA :
            std::cout << "GAMMA" << std::endl;
            break;
        case ETA :
            std::cout << "ETA" << std::endl;
            break;
        default:
            std::cout << "none" << std::endl;
            break;
    }

    std::cout << e << std::endl;

}