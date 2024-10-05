# Compiler and compiler flags
CXX = g++
CXXFLAGS = -Wall -std=c++11

# Executable name
TARGET = convex_hall

# Source files
SRCS = main.cpp ConvexHall.cpp

# Header files
HEADERS = ConvexHall.hpp

# Object files
OBJS = $(SRCS:.cpp=.o)

# Build the target executable
$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS)

# Compile the source files into object files
%.o: %.cpp $(HEADERS)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean up object files and the executable
clean:
	rm -f $(OBJS) $(TARGET)

.PHONY: clean