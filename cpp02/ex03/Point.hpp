#ifndef POINT_H
#define POINT_H

#include "Fixed.hpp"

class Point {
public:
    Point();
    Point(float x, float y);
    Point(const Point& other);
    Point& operator=(const Point& other);
    ~Point();

    Fixed getX() const;
    Fixed getY() const;

private:
    Fixed const x;
    Fixed const y;

};

bool bsp(Point const a, Point const b, Point const c, Point const point);

#endif
