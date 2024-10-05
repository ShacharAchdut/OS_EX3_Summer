#ifndef SERVER_HPP
#define SERVER_HPP

#include <map>
#include <set>
#include <string>
#include <utility>
#include <sys/socket.h>
#include <netinet/in.h>

// מבנה הנתונים עבור הלקוח
extern std::map<int, std::set<std::pair<int, int>>> graphs; 

// פונקציות להוספת גרף וקשתות
void Newgraph(int client_id, int numVertices, int numEdges);
void Newedge(int client_id, int u, int v);
void Removeedge(int client_id, int u, int v);

// פונקציה לחישוב Convex Hull
void calculateConvexHall(int client_fd);

// פונקציה לטיפול בבקשות מלקוחות
void handle_client(int client_fd, fd_set &master_set, fd_set &read_fds);

// הגדרות עבור הגדרות הקשורות לשרת
#define PORT 9034
#define MAX_CLIENTS 10
#define BUFFER_SIZE 1024

#endif // SERVER_HPP