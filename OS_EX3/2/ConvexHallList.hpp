#ifndef CONVEX_HALL_LIST_HPP
#define CONVEX_HALL_LIST_HPP

#include <iostream>
#include <list>
#include <cmath>
#include "Point.hpp"

class ConvexHallList {
public:
    int orientation(Point p, Point q, Point r);
    float convexHallArea(std::list<Point>& points);
    std::list<Point> readPoints();
};

#endif 