CXX = g++
CXXFLAGS = -std=c++11 -Wall -Wextra -pedantic

# קבצים הנדרשים
SERVER_SOURCES = server.cpp ConvexHall.cpp
CLIENT_SOURCES = client.cpp

# קובצי פלט
SERVER_EXEC = server
CLIENT_EXEC = client

# בניית כל הקבצים
all: $(SERVER_EXEC) $(CLIENT_EXEC)

# בניית השרת
$(SERVER_EXEC): $(SERVER_SOURCES)
	$(CXX) $(CXXFLAGS) $(SERVER_SOURCES) -o $(SERVER_EXEC)

# בניית הלקוח
$(CLIENT_EXEC): $(CLIENT_SOURCES)
	$(CXX) $(CXXFLAGS) $(CLIENT_SOURCES) -o $(CLIENT_EXEC)

# ניקיון קבצים שנוצרו
clean:
	rm -f $(SERVER_EXEC) $(CLIENT_EXEC)