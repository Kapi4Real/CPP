
#include <iostream>
#include <cmath>
#include "Fixed.hpp"

std::ostream& operator<<(std::ostream& os, const Fixed& f) 
{
	os << f.toFloat();
	return os;
}


const int Fixed::_fractionalBits = 8;


int Fixed::toInt(void) const 
{
	return _value >> _fractionalBits;
}

float Fixed::toFloat(void) const 
{
	return (float)_value / (1 << _fractionalBits);
}


Fixed::Fixed(int n) 
{
	std::cout << "Int constructor called" << std::endl;
	_value = n << _fractionalBits;
}

Fixed::Fixed(float f) 
{
	std::cout << "Float constructor called" << std::endl;
	_value = static_cast<int>(roundf(f * (1 << _fractionalBits)));
}

Fixed::Fixed() 
{
	std::cout << "Default constructor called" << std::endl;
	_value = 0;
}

Fixed::~Fixed() 
{
	std::cout << "Destructor called" << std::endl;
}

Fixed::Fixed(const Fixed &other) 
{
	std::cout << "Copy constructor called" << std::endl;
	_value = other._value;
}

Fixed& Fixed::operator=(const Fixed& other)
{
	std::cout << "Copy assignment operator called" << std::endl;
	if (this != &other)
		_value = other._value;
	return *this;
}

int Fixed::getRawBits(void) const 
{
	std::cout << "getRawBits member function called" << std::endl;
	return _value;
}

void Fixed::setRawBits(int const raw) 
{
	_value = raw;
}
