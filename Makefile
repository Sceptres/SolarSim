# Compiler
CXX = g++

# Default compiler flags (for all OS)
CXXFLAGS = -std=c++20

# Linker flags for all OS
LDFLAGS = -L$(LIBDIR) -lglfw3 -lpthread

# Detect the operating system using uname
UNAME_S := $(shell uname -s)

# OS-specific linker flags
ifeq ($(UNAME_S), Linux)
    OS_LDFLAGS = -lGL -lGLU -lXrandr -lXi -ldl -lX11
endif

ifeq ($(UNAME_S), Darwin)
    OS_LDFLAGS = -framework OpenGL -framework Foundation -framework AppKit -framework IOKit
endif

ifeq ($(UNAME_S), Windows_NT)
    OS_LDFLAGS = -lopengl32 -lglu32
endif

# Combine default and OS-specific linker flags
LDFLAGS += $(OS_LDFLAGS)

# Directories
SRCDIR = src
OBJDIR = obj
BINDIR = src
INCDIR = # Include dir that contains glfw3, glad, and GLM header files
LIBDIR = # Lib dir that contains glfw3, glad, and GLM library files

# Files and executables
TARGET = $(BINDIR)/SolarSim
SOURCES = $(shell find $(SRCDIR) -name '*.cpp')
OBJECTS = $(patsubst $(SRCDIR)/%.cpp,$(OBJDIR)/%.o,$(SOURCES)) $(OBJDIR)/glad.o

# Rules
all: $(TARGET)

# Link the object files to create the executable
$(TARGET): $(OBJECTS)
	@mkdir -p $(BINDIR)
	$(CXX) $(OBJECTS) $(LDFLAGS) -o $(TARGET)

# Compile the source files into object files
$(OBJDIR)/%.o: $(SRCDIR)/%.cpp
	@mkdir -p $(dir $@)  # Ensure the subdirectories exist
	$(CXX) $(CXXFLAGS) -I$(INCDIR) -c $< -o $@

$(OBJDIR)/glad.o: $(SRCDIR)/glad.c
	@mkdir -p $(OBJDIR)
	$(CXX) $(CXXFLAGS) -I$(INCDIR) -c $< -o $@

# Clean rule to remove generated files
clean:
	rm -rf $(OBJDIR)
	rm $(TARGET)

# Phony targets to avoid conflicts with file names
.PHONY: all clean