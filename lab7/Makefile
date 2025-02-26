.SUFFIXES:         # remove all the implicit rules (avoid conflicts with our own rules)
.SECONDARY:        # all files are intermediate (keep them, otherwise they are removed)
.PHONY: all clean  # these targets are not files (even if a file named "all" or "clean" exists, the rule is applied)

LDFLAGS=
LIBS=
CFLAGS=-Wall -Werror -std=c++20 -g
BIN=treemap
COMPILER = g++

# List of all source files
SRCS = monster.cpp

# Generate the list of object files based on source files
OBJS = $(SRCS:.cpp=.o)

# Default target
all: $(BIN)

# Link all object files to create the final executable
$(BIN): $(OBJS)
	$(COMPILER) $(LDFLAGS) -o $@ $^ $(LIBS)

# Compile each .cpp to .o
%.o: %.cpp
	$(COMPILER) $(CFLAGS) -o $@ -c $<

# Clean up generated files
clean:
	rm -f $(BIN) $(OBJS) *~
