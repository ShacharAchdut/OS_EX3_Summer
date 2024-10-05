#ifndef CONVEXHALL_HPP
#define CONVEXHALL_HPP

#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

class Point {
public:
    float x, y;
    Point() : x(0), y(0) {}

    // Parameterized constructor
    Point(int x, int y) : x(x), y(y) {}
};


class ConvexHall {
public:
    int orientation(Point p, Point q, Point r);
    float convexHallArea(std::vector<Point>& points);
    std::vector<Point> readPoints();

};

#endif