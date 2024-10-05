# Compiler
CXX = g++

# Compiler flags
CXXFLAGS = -Wall -g -pthread

# Source files
SOURCES = main.cpp Proactor.cpp

# Object files (replace .cpp with .o)
OBJECTS = $(SOURCES:.cpp=.o)

# Executable name
EXECUTABLE = server

# Default target
all: $(EXECUTABLE)

# Rule to link object files into executable
$(EXECUTABLE): $(OBJECTS)
	$(CXX) $(CXXFLAGS) -o $@ $^

# Rule to compile source files into object files
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $<

# Clean up generated files
clean:
	rm -f $(OBJECTS) $(EXECUTABLE)
