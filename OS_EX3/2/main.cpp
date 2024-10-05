#include <iostream>
#include "ConvexHallDeque.hpp"
#include "ConvexHallList.hpp"

int main() {
    int choice;
    std::cout << "Choose data structure for Convex Hull calculation:\n";
    std::cout << "1. Deque\n";
    std::cout << "2. List\n";
    std::cout << "Enter your choice (1 or 2): ";
    std::cin >> choice;

    if (choice == 1) {
        // Using ConvexHall with Deque
        ConvexHallDeque convexHallDeque;
        std::deque<Point> points = convexHallDeque.readPoints();
        float area = convexHallDeque.convexHallArea(points);
        std::cout << "The area of the Convex Hull (Deque) is: " << area << std::endl;

    } else if (choice == 2) {
        // Using ConvexHall with List
        ConvexHallList convexHallList;
        std::list<Point> points = convexHallList.readPoints();
        float area = convexHallList.convexHallArea(points);
        std::cout << "The area of the Convex Hull (List) is: " << area << std::endl;

    } else {
        std::cout << "Invalid choice. Please run the program again." << std::endl;
        return 1; // Exit with an error code
    }

    return 0;
}