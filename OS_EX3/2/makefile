# Compiler and flags
CXX = g++
CXXFLAGS = -Wall -std=c++11 -pg

# Executable name
EXEC = convex_hull

# Source files
SOURCES = ConvexHallDeque.cpp ConvexHallList.cpp main.cpp

# Object files (derived from source files)
OBJECTS = $(SOURCES:.cpp=.o)

# Header files
HEADERS = point.hpp ConvexHallDeque.hpp ConvexHallList.hpp

# Build target (linking step)
$(EXEC): $(OBJECTS)
	$(CXX) $(CXXFLAGS) -o $(EXEC) $(OBJECTS)

# Compile each source file into an object file
%.o: %.cpp $(HEADERS)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Run the program and generate gprof profiling output
profile: $(EXEC)
	./$(EXEC)

# Analyze the profiling data and save the report to a file
gprof_analysis: $(EXEC)
	./$(EXEC)
	gprof $(EXEC) gmon.out > gprof_report.txt
	cat gprof_report.txt

# Clean target to remove compiled files and profiling data
clean:
	rm -f $(EXEC) $(OBJECTS) gmon.out gprof_report.txt

# Phony targets (these are not files)
.PHONY: clean profile gprof_analysis
