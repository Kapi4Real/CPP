#include "Animal.hpp"
#include <iostream>

Animal::Animal()
{
	std::cout << "Animal default constructor called" << std::endl;
	type = "Animal";
}

Animal::~Animal()
{
	std::cout << "Animal destructor called" << std::endl;
}

void  Animal::makeSound() const 
{
	std::cout << "Animal make a generic sound" << std::endl;
}

std::string Animal::getType()const 
{ 
	return type;
}
