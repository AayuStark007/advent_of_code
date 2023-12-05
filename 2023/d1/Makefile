CXX = g++
CXXFLAGS = -std=c++17 -Wall

# Define the target executable
TARGET = d1

# Define source files
SRCS = d1.cpp
# Define object files based on source files
OBJS = $(SRCS:.cpp=.o)

# Rule for creating the final executable
$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS)

# Rule for creating object files
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $<

# Clean target to clean up object files and executable
clean:
	rm -f $(TARGET) $(OBJS)