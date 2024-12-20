SRC_FILES = main.cpp ../objects/source/boid.cpp ../objects/source/obstacle.cpp ../objects/source/game_manager.cpp ../objects/source/functions.cpp 

BUILD_DIR = ../compile_files

OBJECTS = $(SRC_FILES:../objects/source/%.cpp=$(BUILD_DIR)/%.o)


CXX = g++
CXXFLAGS = -O2 -std=c++17 -Wall -Wextra -Wunreachable-code -Wshadow -Wpedantic
CXXFLAGS_DEBUG = -g

LIBS = -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio -lsfml-network
INC_PATH = /usr/local/include/
LIB_PATH = /usr/local/lib/

TARGET = Execute

all: $(BUILD_DIR) $(TARGET)

$(BUILD_DIR):
	@if not exist "$(BUILD_DIR)" mkdir "$(BUILD_DIR)"

$(TARGET): $(OBJECTS)
	$(CXX) -o $@ $^ -L$(LIB_PATH) $(LIBS)

$(BUILD_DIR)/%.o: ../objects/source/%.cpp
	@if not exist "$(dir $@)" mkdir "$(dir $@)"
	$(CXX) $(CXXFLAGS) $(CXXFLAGS_DEBUG) -o $@ -c $< -I$(INC_PATH)

clean:
	@if exist $(TARGET) del $(TARGET)
	@if exist $(BUILD_DIR) rmdir /s /q $(BUILD_DIR)

.PHONY: all clean
