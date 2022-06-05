#include <iostream>

#include <City.h>


int main(int argc, char const *argv[])
{
    
    City a = City(1, 2.0f);
    City b = a;
    a.priority = 3.0f;

    std::cout << b.index << " : " << b.priority << std::endl;

    return 0;
}
