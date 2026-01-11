#include "HumanA.hpp"
#include <iostream>

HumanA::HumanA(std::string humanName, Weapon &weaponRef) 
		: name(humanName), weapon(weaponRef){};

void HumanA::attack() const
{
	std::cout << name << " attack with their " << weapon.getType() << std::endl;
}

