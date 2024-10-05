#include <iostream>
#include <vector>
#include <list>
#include <algorithm>
#include <functional>
#include <string>
#include <sstream>
#include <pthread.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <signal.h>
#include <atomic>
#include "proactor.hpp"

using namespace std;

#define PORT 9033   // Port we're listening on

int listener;     // Listening socket descriptor

// Function to create a new graph
void Newgraph(int client_id, int numVertices, int numEdges) {
    pthread_mutex_lock(&graph_mutex);
    graphs[client_id].clear();
    pthread_mutex_unlock(&graph_mutex);
}

// Function to add an edge to the graph
void Newedge(int client_id, int u, int v) {
    pthread_mutex_lock(&graph_mutex);
    graphs[client_id].insert({u, v});
    pthread_mutex_unlock(&graph_mutex);
}

// Function to remove an edge from the graph
void Removeedge(int client_id, int u, int v) {
    pthread_mutex_lock(&graph_mutex);
    graphs[client_id].erase({u, v});
    pthread_mutex_unlock(&graph_mutex);
}

// Function to calculate Convex Hull for the current graph
void calculateConvexHall(int client_fd) {
    pthread_mutex_lock(&graph_mutex);
   const std::vector<Point> points;
    for (const auto& edge : graphs[client_fd]) {
        points.push_back(Point(edge.first, edge.second));
    }

    if (points.size() < 3) {
        std::string response = "Convex hull not possible with less than 3 points.\n";
        send(client_fd, response.c_str(), response.size(), 0);
        pthread_mutex_unlock(&graph_mutex);
        return;
    } else {
        float area = convexHallCalculator.convexHallArea(points);
        std::string response = "Convex hull area: " + std::to_string(area) + "\n";
        send(client_fd, response.c_str(), response.size(), 0);
        pthread_mutex_unlock(&graph_mutex);
        return;
    }
}

// Function to handle client requests
void handle_client(int client_fd, fd_set &master_set) {
    char buffer[BUFFER_SIZE];
    int bytes_received = recv(client_fd, buffer, BUFFER_SIZE, 0);
    
    if (bytes_received <= 0) {
        // If no data is received or client disconnected
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
        } else if (token == "Convexhall") {
            calculateConvexHall(client_fd);
        } else {
            std::string unknown_command = "Unknown command.\n";
            send(client_fd, unknown_command.c_str(), unknown_command.size(), 0);
        }
    }
    // Removed the invalid return NULL statement
}

// Signal handler to gracefully shut down the server
void signal_handler(int signum) {
    // Close the listening socket
    close(listener);
    printf("Server shut down gracefully\n");
    exit(signum);
}

int main() {
    int listener; // Listening socket descriptor
    struct sockaddr_in server_addr;

    // Set up signal handlers
    signal(SIGINT, signal_handler);
    signal(SIGTSTP, signal_handler);

    // Create a listening socket
    if ((listener = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
        perror("socket");
        exit(1);
    }

    // Set socket options
    int yes = 1;
    if (setsockopt(listener, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(int)) == -1) {
        perror("setsockopt");
        exit(1);
    }

    // Bind the socket
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(PORT);
    memset(&(server_addr.sin_zero), '\0', 8);

    if (bind(listener, (struct sockaddr *)&server_addr, sizeof(server_addr)) == -1) {
        perror("bind");
        exit(1);
    }

    // Listen for incoming connections
    if (listen(listener, 10) == -1) {
        perror("listen");
        exit(1);
    }

    std::cout << "Server is running on port " << PORT << std::endl;

    // Start the reactor
    g_reactor = Reactor::startReactor();

    // Add the listener socket to the reactor
    Reactor::addFdToReactor(g_reactor, listener, accept_connection);

    // Run the reactor
    static_cast<Reactor*>(g_reactor)->run();

    // This point is reached when the reactor stops
    close(listener);
    std::cout << "Server shut down" << std::endl;

    return 0;
}
