#include "Zombie.hpp"
#include <iostream> 

Zombie::Zombie(std::string zombieName)
{
	name = zombieName;
}

Zombie::~Zombie() 
{
	std::cout << name << " destroyed" << std::endl;
}

void Zombie::announce(void)
{
	std::cout << name << ": BraiiiiiiinnnzzzZ..." << std::endl;
}
