#include "Dog.hpp"
#include <iostream>

Dog::Dog()
{
        std::cout << "Dog constructor called" << std::endl;
        type = "Dog";
	new Brain();
}

Dog::~Dog()
{
        std::cout << "Dog destructor called" << std::endl;
	delete Brain;
}

void  Dog::makeSound() const
{
        std::cout << "Dog barking" << std::endl;
}
