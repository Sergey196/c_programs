CC=g++
CFLAGS=-c -Wall
LDFLAGS=
SOURCE_DIR=src
BUILD_DIR=build
SOURCES=$(SOURCE_DIR)/main.cpp $(SOURCE_DIR)/hello.cpp $(SOURCE_DIR)/factorial.cpp
OBJECTS:=$(SOURCES:$(SOURCE_DIR)/%.cpp=$(BUILD_DIR)/%.o)
EXECUTABLE=bin/hello

all: $(SOURCES) $(EXECUTABLE)
	
$(EXECUTABLE): $(OBJECTS) 
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

$(BUILD_DIR)/%.o: $(SOURCE_DIR)/%.cpp
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm -rf build/*
	rm -rf bin/*
