#ifndef CONVEX_HALL_HPP
#define CONVEX_HALL_HPP

#include <iostream>
#include <vector>
#include <cmath>

// Struct to represent a point
struct Point {
    float x, y;
    Point() : x(0), y(0) {}
    Point(float x, float y) : x(x), y(y) {}
};

class ConvexHall {
public:
    int orientation(Point p, Point q, Point r);
    float convexHallArea(const std::vector<Point>& points);
    void processCommands();  // Function to process commands from stdin
};

#endif