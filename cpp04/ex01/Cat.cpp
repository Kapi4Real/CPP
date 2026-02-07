#include "Cat.hpp"
#include <iostream>

Cat::Cat()
{
        std::cout << "Cat constructor called" << std::endl;
	new Brain();
        type = "Cat";
}

Cat::~Cat()
{
        std::cout << "Cat destructor called" << std::endl;
	delete Brain;
}

void  Cat::makeSound() const
{
        std::cout << "Cat meow" << std::endl;
}
