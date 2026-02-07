
#ifndef FIXED_H
#define FIXED_H

#include <iostream>

class Fixed {
public:
    Fixed();
    Fixed(const Fixed& other);
    Fixed(int n);
    Fixed(float f);
    Fixed& operator=(const Fixed& other);
    ~Fixed();

    int getRawBits(void) const;
    void setRawBits(int const raw);
    float toFloat(void) const;
    int toInt(void) const;

private:
    int _value;
    static const int _fractionalBits;
};

std::ostream& operator<<(std::ostream& os, const Fixed& f);

#endif
