# Compiler
CXX = g++

# Compiler flags
CXXFLAGS = -Wall -Wextra -std=c++17

# Directories
SRCDIRS = . algorithm generators/linear_congruential generators/mersenne_twister generators/xoroshiro generators/halton generators/laggedFibonacci generators/chacha20
OBJDIR = obj

# Executable file
TARGET = program

# Source files
SOURCES = $(wildcard $(addsuffix /*.cpp, $(SRCDIRS)))

# Object files
OBJECTS = $(SOURCES:%.cpp=$(OBJDIR)/%.o)

# Compilation rule
all: $(TARGET)

# Linking rule
$(TARGET): $(OBJECTS)
	$(CXX) $(CXXFLAGS) -o $@ $^

# Object files compilation rule
$(OBJDIR)/%.o: %.cpp
	mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) -c -o $@ $<

# Clean rule
clean:
	rm -f $(OBJDIR)/**/*.o $(TARGET)

# Run rule
run: $(TARGET)
	./$(TARGET)

.PHONY: all clean run
