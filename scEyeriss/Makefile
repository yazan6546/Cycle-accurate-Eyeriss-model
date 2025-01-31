# Compiler and flags
CXX = g++
CXXFLAGS = -I. -I../systemc-2.3.3/include -L../systemc-2.3.3/lib-linux64 -lsystemc -lm

# List all source files
SRC = $(wildcard *.cpp)  # Get all .cpp files in the folder
OBJ = $(SRC:.cpp=.o)     # Convert .cpp to .o

# Target executable
output_file: $(OBJ)
	$(CXX) -o $@ $^ $(CXXFLAGS)

# Rule to compile .cpp to .o
%.o: %.cpp
	$(CXX) -c $< -o $@ $(CXXFLAGS)

# Clean build files
clean:
	rm -f *.o output_file
