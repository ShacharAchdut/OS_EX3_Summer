#include "server.hpp"
#include "ConvexHall.hpp"
#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <cstring>
#include <vector>
#include <map>
#include <set>

#define PORT 9034
#define MAX_CLIENTS 10
#define BUFFER_SIZE 1024

// מבנה נתונים גלובלי שמכיל את כל הגרפים של המשתמשים
std::map<int, std::set<std::pair<int, int>>> graphs;  // Client ID -> Set of edges
ConvexHall convexHullCalculator;

// פונקציה ליצירת גרף חדש
void Newgraph(int client_id, int numVertices, int numEdges) {
    graphs[client_id].clear();
    std::cout << "Client " << client_id << ": Created new graph with " << numVertices << " vertices." << std::endl;
}

// פונקציה להוספת קשת לגרף
void Newedge(int client_id, int u, int v) {
    graphs[client_id].insert({u, v});
    std::cout << "Client " << client_id << ": Added edge (" << u << ", " << v << ")." << std::endl;
}

// פונקציה להסרת קשת מהגרף
void Removeedge(int client_id, int u, int v) {
    graphs[client_id].erase({u, v});
    std::cout << "Client " << client_id << ": Removed edge (" << u << ", " << v << ")." << std::endl;
}

// פונקציה לחישוב Convex Hull עבור הגרף הנוכחי
void ConvexHull(int client_fd) {
    // המרה של הגרף לנקודות עבור חישוב ה-Convex Hull
    std::vector<Point> points;
    for (const auto& edge : graphs[client_fd]) {
        points.push_back(Point(edge.first, edge.second));
    }

    if (points.size() < 3) {
        std::string response = "Convex hull not possible with less than 3 points.\n";
        send(client_fd, response.c_str(), response.size(), 0);
    } else {
        float area = convexHullCalculator.convexHallArea(points);
        std::string response = "Convex hull area: " + std::to_string(area) + "\n";
        send(client_fd, response.c_str(), response.size(), 0);
    }
}

// פונקציה לטיפול בבקשות מלקוחות
void handle_client(int client_fd, fd_set &master_set, fd_set &read_fds) {
    char buffer[BUFFER_SIZE];
    int bytes_received = recv(client_fd, buffer, BUFFER_SIZE, 0);
    
    if (bytes_received <= 0) {
        // אם לא התקבלו נתונים או שהלקוח התנתק
        close(client_fd);
        FD_CLR(client_fd, &master_set);
        std::cout << "Client " << client_fd << " disconnected." << std::endl;
    } else {
        buffer[bytes_received] = '\0';
        std::string command(buffer);
        std::istringstream iss(command);
        std::string token;
        iss >> token;

        if (token == "Newgraph") {
            int numVertices, numEdges;
            iss >> numVertices >> numEdges;
            Newgraph(client_fd, numVertices, numEdges);
        } else if (token == "Newedge") {
            int u, v;
            iss >> u >> v;
            Newedge(client_fd, u, v);
        } else if (token == "Removeedge") {
            int u, v;
            iss >> u >> v;
            Removeedge(client_fd, u, v);
        } else if (token == "Convexhull") {
            ConvexHull(client_fd);
        } else {
            std::string unknown_command = "Unknown command.\n";
            send(client_fd, unknown_command.c_str(), unknown_command.size(), 0);
        }
    }
}

int main() {
    int server_fd, new_socket;
    struct sockaddr_in address;
    int opt = 1;
    int addrlen = sizeof(address);
    fd_set master_set, read_fds;
    int max_sd;

    // יצירת השרת
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }

    // אופציות ל-Socket
    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR, (char *)&opt, sizeof(opt)) < 0) {
        perror("setsockopt");
        exit(EXIT_FAILURE);
    }

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);

    // חיבור השרת לפורט
    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0) {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }

    // השרת מאזין ללקוחות
    if (listen(server_fd, MAX_CLIENTS) < 0) {
        perror("listen");
        exit(EXIT_FAILURE);
    }

    // איפוס של קבוצת הקבצים
    FD_ZERO(&master_set);
    FD_SET(server_fd, &master_set);
    max_sd = server_fd;

    std::cout << "Server listening on port " << PORT << std::endl;

    while (true) {
        read_fds = master_set;

        // שימוש ב-select לטיפול בלקוחות מרובים
        if (select(max_sd + 1, &read_fds, NULL, NULL, NULL) < 0) {
            perror("select error");
            exit(EXIT_FAILURE);
        }

        // טיפול בבקשות חדשות
        for (int i = 0; i <= max_sd; i++) {
            if (FD_ISSET(i, &read_fds)) {
                if (i == server_fd) {
                    // חיבור חדש
                    if ((new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t *)&addrlen)) < 0) {
                        perror("accept");
                        exit(EXIT_FAILURE);
                    }
                    FD_SET(new_socket, &master_set);
                    if (new_socket > max_sd) {
                        max_sd = new_socket;
                    }
                    std::cout << "New connection: socket fd is " << new_socket << std::endl;
                } else {
                    // טיפול בלקוח קיים
                    handle_client(i, master_set, read_fds);
                }
            }
        }
    }

    return 0;
}