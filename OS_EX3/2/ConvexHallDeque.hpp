#ifndef CONVEX_HALL_DEQUE_HPP
#define CONVEX_HALL_DEQUE_HPP

#include <iostream>
#include <deque>
#include <cmath>
#include "Point.hpp"



class ConvexHallDeque {
public:
    int orientation(Point p, Point q, Point r);
    float convexHallArea(std::deque<Point>& points);
    std::deque<Point> readPoints();
};

#endif