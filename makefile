CXX = g++
CXXFLAGS = -Wall -std=c++17
TARGET = build/bin/my_program
OBJDIR = build/obj
SRCDIR = src
INCLUDEDIR = include

# List of source files
SRCS = $(wildcard $(SRCDIR)/*.cpp)
# SRCS = $(wildcard $(SRCDIR)/**/*.cpp) # Add this back if you add more directories into the src

# Generate object file paths in OBJDIR corresponding to source files
OBJS = $(patsubst $(SRCDIR)/%.cpp, $(OBJDIR)/%.o, $(SRCS))

# Default target: build the executable
all: $(TARGET)

# Create the executable by linking the object files
$(TARGET): $(OBJS)
	@mkdir -p $(dir $(TARGET))
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS)

# Rule to compile .cpp files into .o files, placing them in OBJDIR
$(OBJDIR)/%.o: $(SRCDIR)/%.cpp
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) -I$(INCLUDEDIR) -c $< -o $@

# Clean the build files
clean:
	rm -rf build

# Run the program
run: $(TARGET)
	./$(TARGET)
