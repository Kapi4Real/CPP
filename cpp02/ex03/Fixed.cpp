
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
	_value = n << _fractionalBits;
}

Fixed::Fixed(float f) 
{
	_value = static_cast<int>(roundf(f * (1 << _fractionalBits)));
}

Fixed::Fixed() 
{
	_value = 0;
}

Fixed::~Fixed() {}

Fixed Fixed::operator-(const Fixed& other) const 
{
	Fixed result;
	result.setRawBits(this->getRawBits() - other.getRawBits());
	return result;
}

Fixed Fixed::operator*(const Fixed& other) const 
{
	Fixed result;
	result.setRawBits((this->_value * other._value) >> _fractionalBits);
	return result;
}

bool Fixed::operator>(const Fixed& other) const 
{
	return this->_value > other._value;
}

bool Fixed::operator<(const Fixed& other) const 
{
	return this->_value < other._value;
}

Fixed::Fixed(const Fixed &other) 
{
	_value = other._value;
}

Fixed& Fixed::operator=(const Fixed& other) 
{
	if (this != &other)
		_value = other._value;
	return *this;
}

int Fixed::getRawBits(void) const 
{
	return _value;
}

void Fixed::setRawBits(int const raw) 
{
	_value = raw;
}
