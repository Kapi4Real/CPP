
#include <iostream>
#include "Fixed.hpp"

#include "Point.hpp"

int main(void) {
    Fixed a;
    Fixed const b(10);
    Fixed const c(42.42f);
    Fixed const d(b);
    a = Fixed(1234.4321f);
    std::cout << "a is " << a << std::endl;
    std::cout << "b is " << b << std::endl;
    std::cout << "c is " << c << std::endl;
    std::cout << "d is " << d << std::endl;
    std::cout << "a is " << a.toInt() << " as integer" << std::endl;
    std::cout << "b is " << b.toInt() << " as integer" << std::endl;
    std::cout << "c is " << c.toInt() << " as integer" << std::endl;
    std::cout << "d is " << d.toInt() << " as integer" << std::endl;

    Point p1(0, 0);
    Point p2(10, 0);
    Point p3(0, 10);
    Point test(2, 2);
    std::cout << "Is point (2,2) inside triangle? " << (bsp(p1, p2, p3, test) ? "Yes" : "No") << std::endl;

    return 0;
}
