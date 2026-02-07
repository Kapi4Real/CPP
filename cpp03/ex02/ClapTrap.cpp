#include "ClapTrap.hpp"
#include <iostream>

ClapTrap::ClapTrap()
{
	std::cout << "Default constructor called" << std::endl;
	_name = "bot";
	_hitPoints = 10;
	_energyPoints = 10;
	_attackDamage = 0;
}

ClapTrap::ClapTrap(const std::string &name)
{
	std::cout << "Name constructor called" << std::endl;
	_name = name;
	_hitPoints = 10;
	_energyPoints = 10;
	_attackDamage = 0;
}

ClapTrap::~ClapTrap() 
{
        std::cout << "Destructor called" << std::endl;
}

ClapTrap::ClapTrap(const ClapTrap &other) 
{
        std::cout << "Copy constructor called" << std::endl;
	_name = other._name;
        _hitPoints = other._hitPoints;
        _energyPoints = other._energyPoints;
        _attackDamage = other._attackDamage;

}

ClapTrap& ClapTrap::operator=(const ClapTrap& other) 
{
        std::cout << "Copy assignment operator called" << std::endl;
        if (this != &other)
	{
                _name = other._name;
		_hitPoints = other._hitPoints;
		_energyPoints = other._energyPoints;
                _hitPoints = other._hitPoints;
                _energyPoints = other._energyPoints;
                _attackDamage = other._attackDamage;
	}

        return *this;
}

void ClapTrap::attack(const std::string &target)
{
	if (_energyPoints > 0 && _hitPoints > 0)
	{
		_energyPoints -= 1;
		std::cout << "ClapTrap " << _name << " attacks " << target << " causing " << _attackDamage << " points of damage !" << std::endl;
	}

	else
    	{
        	std::cout << "ClapTrap " << _name << " cannot attack (no energy or hit points)!" << std::endl;
    	}
}


void ClapTrap::takeDamage(unsigned int amount)
{
	       if (_hitPoints <= 0)
		       std::cout << "hitPoints = 0 , we can't take more damage" << std::endl;
	else
	{
			if (static_cast<unsigned int>(_hitPoints) > amount)
		       {
			       _hitPoints -= amount;
			       std::cout << "ClapTrap " << _name << " takes " << amount << " point of damage!" << std::endl;
		       }
		       else
		       {
			       _hitPoints = 0;
			       std::cout << "ClapTrap " << _name << " is destroyed!" << std::endl;
		       }
	}
}

void ClapTrap::beRepaired(unsigned int amount)
{
	if (_energyPoints > 0 && _hitPoints > 0)
	{
		_energyPoints -= 1;
		_hitPoints += amount;
		std::cout << "ClapTrap " << _name << " is repaired for " << amount << " hit points!" << std::endl;
	}

	else 
	{
		std::cout << "we can't heal bot :( " << std::endl;
	}

}
