#include "Dog.hpp"
#include <iostream>


Dog::Dog()
{
        std::cout << "Dog constructor called" << std::endl;
        type = "Dog";
        brain = new Brain();
}


Dog::Dog(const Dog& other) : Animal(other)
{
        std::cout << "Dog copy constructor called" << std::endl;
        type = other.type;
        brain = new Brain(*other.brain);
}

Dog& Dog::operator=(const Dog& other)
{
        std::cout << "Dog assignment operator called" << std::endl;
        if (this != &other)
        {
                Animal::operator=(other);
                type = other.type;
                if (brain)
                        delete brain;
                brain = new Brain(*other.brain);
        }
        return *this;
}

Dog::~Dog()
{
        std::cout << "Dog destructor called" << std::endl;
        delete brain;
}

void Dog::setIdea(int index, const std::string& idea)
{
        if (brain)
                brain->setIdea(index, idea);
}

std::string Dog::getIdea(int index) const
{
        if (brain)
                return brain->getIdea(index);
        return "";
}

void  Dog::makeSound() const
{
        std::cout << "Dog barking" << std::endl;
}
