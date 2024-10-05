#include "ConvexHallDeque.hpp"
#include <iostream>
#include <deque>
#include <cmath>
#include <algorithm>
using namespace std;

// Function to find the orientation of the triplet (p, q, r)
// Returns:
// 0 --> p, q and r are collinear
// 1 --> Clockwise
// 2 --> Counterclockwise
int ConvexHallDeque::orientation(Point p, Point q, Point r) {
    float val = (q.y - p.y) * (r.x - q.x) - (q.x - p.x) * (r.y - q.y);

    if (std::abs(val) < 1e-9) {
        return 0;  // collinear
    }
    return (val > 0) ? 1 : 2; // clockwise or counterclockwise
}

// Function to calculate the area of the convex hull given a set of points
float ConvexHallDeque::convexHallArea(std::deque<Point>& points) {
    int n = points.size();
    if (n < 3) return 0.0; // Convex hull not possible with less than 3 points

    // Sort the points based on x coordinate (or y if x is the same)
    std::sort(points.begin(), points.end(), [](Point a, Point b) {
        return (a.x < b.x) || (a.x == b.x && a.y < b.y);
    });

    std::deque<Point> hull;

    // Build the lower hull
    for (int i = 0; i < n; ++i) {
        while (hull.size() > 1 && orientation(hull[hull.size() - 2], hull.back(), points[i]) != 2) {
            hull.pop_back();
        }
        hull.push_back(points[i]);
    }

    // Build the upper hull
    int lowerHullSize = hull.size();
    for (int i = n - 1; i >= 0; --i) {
        while (hull.size() > lowerHullSize && orientation(hull[hull.size() - 2], hull.back(), points[i]) != 2) {
            hull.pop_back();
        }
        hull.push_back(points[i]);
    }

    // Remove the last point because it's the same as the first point in a closed hull
    hull.pop_back();

    // Calculate the area of the convex hull using the shoelace formula
    float area = 0.0;
    for (int i = 0; i < hull.size(); ++i) {
        int j = (i + 1) % hull.size();
        area += hull[i].x * hull[j].y - hull[i].y * hull[j].x;
    }
    area = std::abs(area) / 2.0;
    return area;
}

// Function to read points from the input
std::deque<Point> ConvexHallDeque::readPoints() {
    std::deque<Point> points;
    int n;
    std::cout << "Enter the number of points: ";
    std::cin >> n;
    std::cin.ignore();  // Ignore any leftover newline character

    for (int i = 0; i < n; ++i) {
        float x, y;
        char comma;

        std::cout << "Enter x and y for point " << i + 1 << " (format: x,y): ";
        std::cin >> x >> comma >> y;  // Read x, comma, and y
        points.push_back(Point{x, y});
    }

    return points;
}