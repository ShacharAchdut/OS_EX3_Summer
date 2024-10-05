#ifndef POINT_HPP
#define POINT_HPP

class Point {
public:
    float x, y;
    Point() : x(0), y(0) {}

    // Parameterized constructor
    Point(float x, float y) : x(x), y(y) {}
};

#endif