#include "ConvexHall.hpp"
#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
using namespace std;



// Function to find the orientation of the triplet (p, q, r)
// Returns:
// 0 --> p, q and r are collinear
// 1 --> Clockwise
// 2 --> Counterclockwise
int ConvexHall::orientation(Point p, Point q, Point r) {
    float val = (q.y - p.y) * (r.x - q.x) - (q.x - p.x) * (r.y - q.y);

    if (std::abs(val) < 1e-9) {
        return 0;  // collinear
    }
    return (val > 0) ? 1 : 2; // clockwise or counterclockwise
}

// Function to calculate the area of the convex hull given a set of points
float ConvexHall::convexHallArea(std::vector<Point>& points) {
    int n = points.size();
    if (n < 3) return 0.0; // Convex hull not possible with less than 3 points

    // Sort the points based on x coordinate (or y if x is the same)
    std::sort(points.begin(), points.end(), [](Point a, Point b) {
        return (a.x < b.x) || (a.x == b.x && a.y < b.y);
    });

    std::vector<Point> hull;

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
// Function to process verticals and commands from stdin
void ConvexHall::processCommands() {
    std::vector<Point> points;
    std::string command;
     std::cout << "ENTER YOUR COMMAND PLEASE"  << std::endl;
    
    while (std::cin >> command) {
        if (command == "Newgraph") {
           int n;
            std::cout << "Enter the number of points: ";
            std::cin >> n;
            std::cin.ignore();  // Ignore any leftover newline character
            points.clear();
            for (int i = 0; i < n; ++i) {
                float x, y;
                char comma;

            std::cout << "Enter x and y for point " << i + 1 << " (format: x,y): ";
            std::cin >> x >> comma >> y;  // Read x, comma, and y
            points.push_back(Point(x, y));
            }
            std::cout << "Graph with " << n << " points created." << std::endl;
        } 
        else if (command == "Convexhull") {
            if (points.size() < 3) {
                std::cout << "Convex hull not possible with less than 3 points." << std::endl;
            } else {
                float area = convexHallArea(points);
                std::cout << "Convex hull area: " << area << std::endl;
            }
        } 
        else if (command == "Newpoint") {
            float x, y;
            char comma;
            std::cout << "Enter the value of the point. (format: X,Y)" << std::endl;
            std::cin >> x >> comma >> y;
            points.push_back(Point(x, y));
            std::cout << "Point (" << x << ", " << y << ") added." << std::endl;
        } 
        else if (command == "Removepoint") {
            float x, y;
            char comma;
            std::cout << "Which point would you like to remove?(format: X,Y)"<< std::endl;
            std::cin >> x>> comma >> y;
            auto it = std::remove_if(points.begin(), points.end(), [&](Point p) {
                return p.x == x && p.y == y;
            });
            if (it != points.end()) {
                points.erase(it, points.end());
                std::cout << "Point (" << x << ", " << y << ") removed." << std::endl;
            } else {
                std::cout << "Point (" << x << ", " << y << ") not found." << std::endl;
            }
        } 
        else {
            std::cout << "Unknown command: " << command << std::endl;
        }
    }
}
