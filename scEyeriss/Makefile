# Compiler and flags
CXX = g++
CXXFLAGS = -I. -I../systemc-2.3.3/include
LDFLAGS = -L../systemc-2.3.3/lib-linux64 -lsystemc -lm

# List all source files
SRC = $(wildcard *.cpp)  # Get all .cpp files in the folder
OBJ = $(SRC:.cpp=.o)     # Convert .cpp to .o

# Target executable
output_file: $(OBJ)
	$(CXX) -o $@ $^ $(LDFLAGS)

# Rule to compile .cpp to .o
%.o: %.cpp
	$(CXX) -c $< -o $@ $(CXXFLAGS)

# Run the executable
.PHONY: run
run: output_file
	LD_LIBRARY_PATH=../systemc-2.3.3/lib-linux64:$$LD_LIBRARY_PATH ./output_file

# Clean build files
clean:
	rm -f *.o output_file