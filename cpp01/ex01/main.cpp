#include "Zombie.hpp"
#include <iostream>

int main()
{
    int N;
    std::string name;
    
    std::cout << "Number of zombie :";
    std::cin >> N;
    if (N <= 0)
    {
        std::cerr << "Error: N must be positive" << std::endl;
        return (1);
    }
    std::cin.ignore();
    std::cout << "Name of zombie :";
    std::getline(std::cin,name);
    Zombie* horde = zombieHorde(N,name);

    for(int i =0;i < N;i++)
    {
	    horde[i].announce();
    }
    delete[] horde;
    return(0);
}
