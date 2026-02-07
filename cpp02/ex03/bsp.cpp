#include "Point.hpp"

static Fixed cross(Point const &a, Point const &b, Point const &c) {
    Fixed abx = b.getX() - a.getX();
    Fixed aby = b.getY() - a.getY();
    Fixed acx = c.getX() - a.getX();
    Fixed acy = c.getY() - a.getY();
    return abx * acy - aby * acx;
}

bool bsp(Point const a, Point const b, Point const c, Point const point) {
    Fixed d1 = cross(point, a, b);
    Fixed d2 = cross(point, b, c);
    Fixed d3 = cross(point, c, a);
    bool has_neg = (d1 < 0) || (d2 < 0) || (d3 < 0);
    bool has_pos = (d1 > 0) || (d2 > 0) || (d3 > 0);
    return !(has_neg && has_pos);
}
