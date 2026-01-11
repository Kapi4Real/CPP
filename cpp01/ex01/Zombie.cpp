#include "Zombie.hpp"
#include <iostream>

Zombie::Zombie() {}

Zombie::Zombie(std::string zombieName)
{
    name = zombieName;
}

Zombie::~Zombie()
{
    std::cout << name << " destroyed" << std::endl;
}

void Zombie::setName(std::string newName) 
{
    name = newName;
}

void Zombie::announce(void) 
{
    std::cout << name << ": BraiiiiiiinnnzzzZ..." << std::endl;
}
