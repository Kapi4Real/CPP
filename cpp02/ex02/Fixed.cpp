

#include <iostream>
#include <cmath>
#include "Fixed.hpp"

const int Fixed::_fractionalBits = 8;

Fixed::Fixed()
{
    std::cout << "Default constructor called" << std::endl;
    _value = 0;
}

Fixed::Fixed(const Fixed &other)
{
    std::cout << "Copy constructor called" << std::endl;
    _value = other._value;
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

Fixed::~Fixed() 
{
    std::cout << "Destructor called" << std::endl;
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

int Fixed::toInt(void) const 
{
    return _value >> _fractionalBits;
}

float Fixed::toFloat(void) const 
{
    return (float)_value / (1 << _fractionalBits);
}

Fixed Fixed::operator+(const Fixed& other) const 
{
    Fixed result;
    result.setRawBits(this->getRawBits() + other.getRawBits());
    return result;
}

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

Fixed Fixed::operator/(const Fixed& other) const 
{
    Fixed result;
    result.setRawBits((this->_value << _fractionalBits) / other._value);
    return result;
}

Fixed& Fixed::operator++() 
{
    _value += 1;
    return *this;
}

Fixed Fixed::operator++(int) 
{
    Fixed temp = *this;
    _value += 1;
    return temp;
}

Fixed& Fixed::operator--() 
{
    _value -= 1;
    return *this;
}

Fixed Fixed::operator--(int) 
{
    Fixed temp = *this;
    _value -= 1;
    return temp;
}

bool Fixed::operator>(const Fixed& other) const 
{
    return this->_value > other._value;
}

bool Fixed::operator<(const Fixed& other) const 
{
    return this->_value < other._value;
}

bool Fixed::operator>=(const Fixed& other) const 
{
    return this->_value >= other._value;
}

bool Fixed::operator<=(const Fixed& other) const 
{
    return this->_value <= other._value;
}

bool Fixed::operator==(const Fixed& other) const 
{
    return this->_value == other._value;
}

bool Fixed::operator!=(const Fixed& other) const 
{
    return this->_value != other._value;
}

Fixed& Fixed::min(Fixed& a, Fixed& b) 
{
    return (a < b) ? a : b;
}

const Fixed& Fixed::min(const Fixed& a, const Fixed& b) 
{
    return (a < b) ? a : b;
}

Fixed& Fixed::max(Fixed& a, Fixed& b) 
{
    return (a > b) ? a : b;
}

const Fixed& Fixed::max(const Fixed& a, const Fixed& b) 
{
    return (a > b) ? a : b;
}

std::ostream& operator<<(std::ostream& os, const Fixed& f) 
{
    os << f.toFloat();
    return os;
}
