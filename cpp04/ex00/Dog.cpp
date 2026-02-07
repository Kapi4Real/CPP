#include "Dog.hpp"
#include <iostream>

Dog::Dog()
{
        std::cout << "Dog constructor called" << std::endl;
        type = "Dog";
}

Dog::~Dog()
{
        std::cout << "Dog destructor called" << std::endl;
}

void  Dog::makeSound() const
{
        std::cout << "Dog barking" << std::endl;
}

