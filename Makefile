CXX = g++
CXXFLAGS = -std=c++11 -Wall -Wextra -O2
TARGET = autorank
SRCDIR = src
BUILDDIR = build
SOURCES = $(wildcard $(SRCDIR)/core/*.cpp) $(wildcard $(SRCDIR)/structures/*.cpp) $(wildcard $(SRCDIR)/utils/*.cpp) $(wildcard $(SRCDIR)/interface/*.cpp)
OBJECTS = $(SOURCES:$(SRCDIR)/%.cpp=$(BUILDDIR)/%.o)

.PHONY: all clean

all: $(TARGET)

$(TARGET): $(OBJECTS)
	@echo "Linking $@..."
	@$(CXX) $(OBJECTS) -o $(TARGET)
	@echo "Build complete!"

$(BUILDDIR)/%.o: $(SRCDIR)/%.cpp
	@mkdir -p $(dir $@)
	@echo "Compiling $<..."
	@$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	@echo "Cleaning build files..."
	@rm -rf $(BUILDDIR) $(TARGET)
	@echo "Clean complete!"

run: $(TARGET)
	./$(TARGET)

debug: CXXFLAGS += -g -DDEBUG
debug: $(TARGET)

release: CXXFLAGS += -O3
release: $(TARGET) 
