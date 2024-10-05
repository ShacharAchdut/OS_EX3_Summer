#include "ConvexHall.hpp"
#include <iostream>

int main() {
    ConvexHall convexHall; // Create an instance of ConvexHall

    // Call the methods on the instance
    std::vector<Point> points = convexHall.readPoints();
    float area = convexHall.convexHallArea(points);

    std::cout << "Area of Convex Hull: " << area << std::endl;

    return 0;
}
